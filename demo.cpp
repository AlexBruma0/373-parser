#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>

#include <cpp-tree-sitter.h>

extern "C" {
//TSLanguage *tree_sitter_json();
TSLanguage *tree_sitter_socialgaming();
}



int main() {
    // Create a language and parser.
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};

    // Parse the provided JSON string into a syntax tree.
     std::string sourcecode = R"(
configuration {
  name: ""
  player range: (0, 0)
  audience: false
  setup: {}
}
constants {}
variables {}
per-player {}
per-audience {}
rules {}
    )";
    ts::Tree tree = parser.parseString(sourcecode);

    // Access the root node of the AST
    ts::Node root = tree.getRootNode();
    std::cout << root.getNumChildren() << "\n";
    std::cout << root.getSExpr().get() << "\n";
    ts::Node n = root.getChild(0);
    // std::cout << n.getNumChildren() << "\n";
    //std::cout << n.getChild(0).getSExpr().get() << "\n";
    // for(int i = 0; i < n.getNumChildren(); i++ ){
    //   std::cout << n.getChild(i).getSExpr().get() << "\n";
    // }
    // auto treestring = n.getSExpr();


    // std::cout << treestring.get() << "\n";

    return 0;
}
