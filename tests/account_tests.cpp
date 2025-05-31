#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../banking/Account.h"

using ::testing::Eq;

class AccountTest : public ::testing::Test {
protected:
    Account* account;

    void SetUp() override {
        account = new Account(1, 100);
    }

    void TearDown() override {
        delete account;
    }
};

TEST_F(AccountTest, InitialBalanceIsCorrect) {
    EXPECT_EQ(account->GetBalance(), 100);
}

TEST_F(AccountTest, IdIsCorrect) {
    EXPECT_EQ(account->id(), 1);
}

TEST_F(AccountTest, LockUnlockWorks) {
    account->Lock();
    EXPECT_NO_THROW(account->ChangeBalance(10));
    account->Unlock();
    EXPECT_ANY_THROW(account->ChangeBalance(10));
}

TEST_F(AccountTest, ChangeBalanceOnlyWhenLocked) {
    EXPECT_ANY_THROW(account->ChangeBalance(10));
    account->Lock();
    EXPECT_NO_THROW(account->ChangeBalance(10));
    EXPECT_EQ(account->GetBalance(), 110);
}
