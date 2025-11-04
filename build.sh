#!/usr/bin/env bash
set -e
set -o pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
GENERATOR="Unix Makefiles"

function show_help() {
    echo "Usage: ./build.sh [command] [container]"
    echo "Commands:"
    echo "  all                     Build everything (library + tests + benchmarks)"
    echo "  test                    Build everything and run all tests"
    echo "  test [container]        Build and run tests (all or specific container)"
    echo "  benchmark [container]   Build and run benchmark (all or specific container)"
    echo "  clean                   Remove build directory"
    echo "  help                    Show this message"
    echo
    echo "Examples:"
    echo "  ./build.sh test vector"
    echo "  ./build.sh benchmark unordered_map"
    echo "  ./build.sh all"
}

function clean_build() {
    if [ -d "$BUILD_DIR" ]; then
        echo "Cleaning existing build directory..."
        rm -rf "$BUILD_DIR"
    fi
}

function ensure_build() {
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake -G "$GENERATOR" "$ROOT_DIR" -DCMAKE_BUILD_TYPE=Release
}

function build_all() {
    clean_build
    ensure_build
    cmake --build . --config Release
}

function run_tests() {
    local container="$1"
    clean_build
    ensure_build

    if [ -z "$container" ]; then
        echo "=== Building all tests ==="
        cmake --build . --config Release

        echo "=== Running all tests ==="
        ctest --output-on-failure
    else
        local test_target="${container}_test"
        cmake --build . --target "$test_target"
        echo "=== Running test for $container ==="
        "./$test_target"
    fi
}

function run_benchmarks() {
    local container="$1"
    clean_build
    ensure_build

    if [ -z "$container" ]; then
        echo "=== Running all benchmarks ==="
        for bench_exec in ./benchmarks/*_benchmark; do
            [ -x "$bench_exec" ] || continue
            echo "Running $(basename "$bench_exec")"
            "$bench_exec"
        done
    else
        local bench_exec="${container}_benchmark"
        cmake --build . --target "$bench_exec"
        echo "=== Running benchmark for $container ==="
        "./$bench_exec"
    fi
}

COMMAND="$1"
CONTAINER="$2"

case "$COMMAND" in
    all)
        build_all
        ;;
    test)
        run_tests "$CONTAINER"
        ;;
    benchmark)
        run_benchmarks "$CONTAINER"
        ;;
    clean)
        clean_build
        ;;
    help | "")
        show_help
        ;;
    *)
        echo "Unknown command: $COMMAND"
        show_help
        exit 1
        ;;
esac
