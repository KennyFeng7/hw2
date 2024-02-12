#include "book.h"
#include <iostream>
#include <sstream>
#include "util.h"

std::set<std::string> Book::keywords() const {
  std::set<std::string> result;
  std::set<std::string> keyword = parseStringToWords(name_);
  std::set<std::string>::iterator it;
  for(it = keyword.begin(); it != keyword.end(); ++it){
    result.insert(*it);
  }
  keyword = parseStringToWords(author_);
  for(it = keyword.begin(); it != keyword.end(); ++it){
    result.insert(*it);
  }    
  result.insert(isbn_);
  return result;
}

std::string Book::displayString() const {
  std::ostringstream stream;
  stream << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
         << price_ << " " << qty_ << " left.";
  return stream.str();
}

void Book::dump(std::ostream& os) const {
  Product::dump(os);
  os << isbn_ << "\n" << author_ << std::endl;
}

