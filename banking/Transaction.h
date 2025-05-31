#pragma once

#include "Account.h"

class Transaction {
 public:
  Transaction();
  virtual ~Transaction();

  bool Make(Account& from, Account& to, int sum);
  int fee() const { return fee_; }
  void set_fee(int fee) { fee_ = fee_; }

  virtual void SaveToDataBase(Account& from, Account& to, int sum);

 private:
  void Credit(Account& account, int sum);
  bool Debit(Account& account, int sum);

  int fee_;
};
