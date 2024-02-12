#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
  set<Product*> products;
  for(map<string, set<Product*>>::iterator i = keywordsToProducts.begin(); i != keywordsToProducts.end(); ++ i){
    products = setUnion<Product*>(products, i->second);
  }
  for(set<Product*>::iterator it = products.begin(); it != products.end(); ++it){
    delete *it;
  }
  for(map<string, User*>::iterator it = users.begin(); it != users.end(); ++ it){
    delete it->second;
  }
        
  
}

void MyDataStore::addProduct(Product* p) {
  std::set<std::string> keyword = p->keywords();
  set<string>::iterator it;
  for(it = keyword.begin(); it != keyword.end(); ++it){
    map<string, set<Product*>>::iterator item = keywordsToProducts.find(*it);
    if(item == keywordsToProducts.end()){
      keywordsToProducts.insert(pair<string, set<Product*>>(*it, set<Product*>()));
      item = keywordsToProducts.find(*it);
    }
    (item->second).insert(p);
  }
}

void MyDataStore::addUser(User* u) {
  users.insert(pair<string, User*>(u->getName(), u));
  userCarts.insert(pair<string, vector<Product*>>(u->getName(), std::vector<Product*>()));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& searchTerms, int searchType) {
  std::set<Product*> searchResults;

  std::set<Product*> matchedProducts;
  for (std::vector<std::string>::iterator it = searchTerms.begin(); it != searchTerms.end(); ++it) {
    if (keywordsToProducts.find(*it) != keywordsToProducts.end()) {
      matchedProducts = keywordsToProducts[*it];
      if (searchType == 0) { // AND search
        if (searchResults.empty()) {
          searchResults.insert(matchedProducts.begin(),matchedProducts.end());
        } 
        else{
          searchResults = setIntersection(searchResults, matchedProducts);
        }
      } 
      else if (searchType == 1) { // OR search
        if(searchResults.empty()){
          searchResults.insert(matchedProducts.begin(),matchedProducts.end());
        }
        else{
          searchResults = setUnion(searchResults, matchedProducts);
        }
      }
    } 
  }
  std::vector<Product*> finalResults(searchResults.begin(),searchResults.end());
  return finalResults;
}

void MyDataStore::dump(std::ostream& ofile){
  set<Product*> products;
  for(map<string, set<Product*>>::iterator it = keywordsToProducts.begin(); it != keywordsToProducts.end(); ++it){
    products = setUnion<Product*>(products, it->second);
  }
  ofile << "<products>" << endl;
  for(set<Product*>::iterator it = products.begin(); it != products.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl << "<users>" << endl;
  for(map<string, User*>::iterator it = users.begin(); it != users.end(); ++it){
    it->second->dump(ofile);
  } 
  ofile << "</users>" << endl;
  
}

void MyDataStore::viewcart(const std::string& username){
  map<string, vector<Product*>>::iterator item = userCarts.find(username);
  if(item == userCarts.end()){
    cout << "Invalid username" << endl;
    return;
  }
  else{
    vector<Product*> cart(item->second);
    for(size_t i = 0; i < cart.size(); ++ i){
      cout << "Item: " << i + 1 << endl << cart[i]->displayString() << endl;
    }
  }
}

void MyDataStore::addToCart(const std::string& username, Product* product){
  map<string, vector<Product*>>::iterator item = userCarts.find(username);
  if(item == userCarts.end()){
    cout << "Invalid request" << endl;
    return;
  }
  else{
    userCarts[username].push_back(product);
  }
}

void MyDataStore::buycart(const std::string& username) {
  if(users.find(username) == users.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  User* user = users[username];
  auto& cart = userCarts[username];
  auto it = cart.begin();
  while(it != cart.end()) {
    Product* product = *it;
    if(product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
      user->deductAmount(product->getPrice());
      product->subtractQty(1);
      it = cart.erase(it); 
    } 
    else {
      ++it;
    }
  }
}
