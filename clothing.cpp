#include "clothing.h"
#include "util.h"
#include <sstream> 

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> result;
  std::set<std::string> keyword = parseStringToWords(name_);
  std::set<std::string>::iterator it;
  for(it = keyword.begin(); it != keyword.end(); ++it){
    result.insert(*it);
  }
  keyword = parseStringToWords(brand_);
  for(it = keyword.begin(); it != keyword.end(); ++it){
    result.insert(*it);
  }
  return result;
}

std::string Clothing::displayString() const {
  std::ostringstream stream;
  stream << name_ << "\n"
         << "Size: " << size_ << " Brand: " << brand_ << "\n"
         << price_ << " " << qty_ << " left.";
  return stream.str();
}

void Clothing::dump(std::ostream& os) const {
  Product::dump(os);
  os << size_ << "\n" << brand_ << std::endl;
}