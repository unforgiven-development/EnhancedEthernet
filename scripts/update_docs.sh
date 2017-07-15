#!/usr/bin/env bash
#
# Provides a (relatively) automated method of updating the project's documentation
#

SCRIPTS_DIR="$(pwd)"

PROJECT_ROOT="${SCRIPTS_DIR}/.."
PRJ_ROOT="${PROJECT_ROOT}"

DOXYFILE_FILE="${PRJ_ROOT}/Doxyfile"
LIBPROPS_FILE="${PRJ_ROOT}/library.properties"

DOCS_PATH="${PRJ_ROOT}/docs"
DOXYGEN_OUT_PATH="${DOCS_PATH}/doxygen"
DOCS_RESOURCE_PATH="${DOCS_PATH}/resources"

