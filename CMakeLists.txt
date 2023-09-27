cmake_minimum_required(VERSION 3.19)
project(cpp-tree-sitter)

include(cmake/CPM.cmake)
set(CMAKE_CXX_STANDARD 17)

# Downloads this wrapper library and tree-sitter.
# Makes them available via the `cpp-tree-sitter` CMake library target.
CPMAddPackage(
  NAME cpp-tree-sitter
  GIT_REPOSITORY https://github.com/nsumner/cpp-tree-sitter.git
  GIT_TAG v0.0.1
)

function(add_grammar_from_repo_no_version NAME REPO TAG)
  CPMAddPackage(
    NAME ${NAME}
    GIT_REPOSITORY ${REPO}
    GIT_TAG ${TAG}
    DOWNLOAD_ONLY YES
  )

  if ("${${NAME}_ADDED}")
    add_library(${NAME})

    file(GLOB maybe_scanner "${${NAME}_SOURCE_DIR}/src/scanner.c")
    target_sources(${NAME}
      PRIVATE
        "${${NAME}_SOURCE_DIR}/src/parser.c"
        ${maybe_scanner}
    )
    target_include_directories(${NAME}
      PRIVATE
        # parser.h is stored within the src directory, so we need to include
        # src in the search paths
        $<BUILD_INTERFACE:${${NAME}_SOURCE_DIR}/src>
      PUBLIC
        $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(${NAME}
      INTERFACE
        tree-sitter
    )
    target_compile_options(${NAME}
      PRIVATE
        "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wno-unused-but-set-variable>"
    )
  endif()
endfunction(add_grammar_from_repo_no_version)

add_grammar_from_repo_no_version(tree-sitter-socialgaming
  https://github.com/nsumner/tree-sitter-socialgaming.git
  7ad013c8773b07e27e7eb7a9e4779d473a85c24f
)

# Use the library in a demo program.
add_executable(demo)
target_sources(demo
  PRIVATE
    demo.cpp
)
target_link_libraries(demo
  tree-sitter-socialgaming
  cpp-tree-sitter
)