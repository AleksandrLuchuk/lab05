#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Подключи заголовочные файлы из папки banking/
#include "../banking/Account.h"
#include "../banking/Transaction.h"

using ::testing::Return;
using ::testing::_;

class MockAccount : public Account {
 public:
  MockAccount(int id, int balance) : Account(id, balance) {}

  MOCK_METHOD(int, GetBalance, (), (const, override));
  MOCK_METHOD(void, ChangeBalance, (int), (override));
  MOCK_METHOD(void, Lock, (), (override));
  MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction : public Transaction {
 public:
  MOCK_METHOD(void, SaveToDataBase, (Account&, Account&, int), (override));
};

TEST(TransactionTest, MakeTransferSuccess) {
  MockAccount from(1, 200);
  MockAccount to(2, 100);

  MockTransaction trans;

  EXPECT_CALL(from, Lock()).Times(1);
  EXPECT_CALL(to, Lock()).Times(1);
  EXPECT_CALL(from, Unlock()).Times(1);
  EXPECT_CALL(to, Unlock()).Times(1);

  EXPECT_CALL(from, GetBalance()).WillOnce(Return(200));
  EXPECT_CALL(from, ChangeBalance(-150)).Times(1);
  EXPECT_CALL(to, ChangeBalance(100)).Times(1);
  EXPECT_CALL(trans, SaveToDataBase(_, _, 100)).Times(1);

  trans.set_fee(50);
  EXPECT_TRUE(trans.Make(from, to, 100));
}
