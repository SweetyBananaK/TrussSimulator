#pragma once
#include "exprtk.hpp"
#include <string>

using T = double;


class Parser_wrapper{
public:
  Parser_wrapper();
  void custom_function(T& x,T& y,T& dxdy);
  bool set_function(std::string function_string);

  void load_function(std::string file);
  void save_function(std::string file, std::string function);

private:

  double symtv;

  exprtk::symbol_table<double> symbol_table;
  exprtk::expression<double> my_expression;
  exprtk::parser<double> parser;
  std::string expr_string = "3000 + x * x";
};
