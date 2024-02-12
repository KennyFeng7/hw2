#include "movie.h"
#include "util.h"
#include <sstream> 

std::set<std::string> Movie::keywords() const {
  std::set<std::string> result;
  std::set<std::string> keyword = parseStringToWords(name_);
  std::set<std::string>::iterator it;
  for(it = keyword.begin(); it != keyword.end(); ++it){
    result.insert(*it);
  }
  std::string genres;
  for(size_t i = 0; i < genre_.size(); i ++){
    genres += std::tolower(genre_[i]);
  }
  result.insert(genres);
  return result;
}

std::string Movie::displayString() const {
  std::ostringstream stream;
  stream << name_ << "\n"
         << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
         << price_ << " " << qty_ << " left.";
  return stream.str();
}

void Movie::dump(std::ostream& os) const {
  Product::dump(os);
  os << genre_ << "\n" << rating_ << std::endl;
}