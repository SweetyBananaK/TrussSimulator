#include "parser.hpp"
#include <fstream>


Parser_wrapper::Parser_wrapper(){
  symbol_table.add_variable("x",symtv);
  my_expression.register_symbol_table(symbol_table);
  parser.compile(expr_string, my_expression);
}

void Parser_wrapper::custom_function(double& x,double& y,double& dxdy)
{
  double yp,ym,dx=fabs(x) < 1 ? sqrt(std::numeric_limits<double>::epsilon())
         : sqrt(std::numeric_limits<double>::epsilon())*fabs(x);

  symtv = x;

  symtv += dx;
  yp = my_expression.value();
  symtv -= 2*dx;
  ym = my_expression.value();
  symtv += dx;
  y = my_expression.value();

  dxdy = (yp-ym)/(2*dx);

  x = symtv;
}

bool Parser_wrapper::set_function(std::string function_string){
  expr_string = function_string;
  return parser.compile(expr_string, my_expression);
}

void Parser_wrapper::load_function(std::string file){
    std::ifstream load_stream;
    load_stream.open(file);
    std::string func;
    load_stream >> func;
    set_function(func);
    load_stream.close();
}
void Parser_wrapper::save_function(std::string file, std::string function){
    std::ofstream save_stream;
    save_stream.open(file);
    save_stream << function;
    save_stream.close();
}
