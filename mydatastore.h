
#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <queue>
#include <vector>

class MyDataStore : public DataStore {
public:
  MyDataStore();
  virtual ~MyDataStore();
  void addProduct(Product* p) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& os) override;
  void addToCart(const std::string& username, Product* p);
  void viewcart(const std::string& username);
  void buycart(const std::string& username);

private:
  std::map<std::string, std::set<Product*>> keywordsToProducts;
  std::map<std::string, std::vector<Product*>> userCarts;
  std::map<std::string, User*> users; 
};

#endif
