#!/bin/sh
# Build the Linux target of Sourcetrail inside Docker and export it to a local folder.
#
# Usage: script/docker/build_linux.sh [output_dir] [extra docker build args...]
#   e.g. script/docker/build_linux.sh release --build-arg RUN_TESTS=ON
set -e

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
OUT="${1:-$ROOT/release}"
[ $# -gt 0 ] && shift

DOCKER_BUILDKIT=1 docker build \
	-f "$ROOT/deployment/dockerfiles/linux/qt6/Dockerfile" \
	--target artifact \
	--output "type=local,dest=$OUT" \
	"$@" \
	"$ROOT"

echo "Built Sourcetrail into $OUT/Sourcetrail"
