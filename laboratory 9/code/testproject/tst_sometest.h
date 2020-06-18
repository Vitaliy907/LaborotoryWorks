#ifndef TST_SOMETEST_H
#define TST_SOMETEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "lockcontroller.h"

using namespace testing;

class MockIKeypad : public IKeypad{
public:
    MOCK_METHOD(
        bool,
        isActive,
        (),
        (override)
    );
    MOCK_METHOD(
        void,
        wait,
        (),
        (override)
    );
    MOCK_METHOD(
        PasswordResponse,
        requestPassword,
        (),
        (override)
    );
};

class MockILatch : public ILatch{
public:
    MOCK_METHOD(
        bool,
        isActive,
        (),
        (override)
    );
    MOCK_METHOD(
        DoorStatus,
        open,
        (),
        (override)
    );
    MOCK_METHOD(
        DoorStatus,
        close,
        (),
        (override)
    );
    MOCK_METHOD(
        DoorStatus,
        getDoorStatus,
        (),
        (override)
    );
};

TEST(LaboratoryTest, Test1){
    //Arrange
    MockIKeypad MockKeyPad;

    ILatch *Latch = nullptr;
    LockController LockerC(&MockKeyPad, Latch);
    //Prepare mocks
    EXPECT_CALL(MockKeyPad, wait())
            .Times(1);
    //Act
    LockerC.wait();
}

TEST(LaboratoryTest, Test2){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    //Prepare mocks

    EXPECT_CALL(MockLatch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    //Assert
    ASSERT_FALSE(LockerC.isDoorOpen());
}

TEST(LaboratoryTest, Test3){
    //Arrange
    IKeypad *KeyPad = nullptr;
    MockILatch MockLatch;
    LockController LockerC(KeyPad, &MockLatch);

    //Prepare mocks

    EXPECT_CALL(MockLatch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    //Assert
    ASSERT_TRUE(LockerC.isDoorOpen());
}

TEST(LaboratoryTest, Test4){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    //Prepare mocks
    EXPECT_CALL(MockLatch, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    //Assert
    ASSERT_EQ(LockerC.unlockDoor(), DoorStatus::OPEN);
}

TEST(LaboratoryTest, Test5){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    //Prepare mocks
    EXPECT_CALL(MockLatch, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    //Assert
    ASSERT_EQ(LockerC.lockDoor(), DoorStatus::CLOSE);
}

TEST(LaboratoryTest, Test6){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    //Prepare mocks

    EXPECT_CALL(MockKeyPad, isActive())
            .Times(1)
            .WillOnce(Return(1));

    EXPECT_CALL(MockLatch, isActive())
            .Times(1)
            .WillOnce(Return(1));

    //Assert
    ASSERT_EQ(LockerC.hardWareCheck(), HardWareStatus::OK);
}

TEST(LaboratoryTest, Test7){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(nullptr, &MockLatch);

    //Prepare mocks

    EXPECT_CALL(MockKeyPad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(1));

    EXPECT_CALL(MockLatch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(1));

    //Assert
    ASSERT_EQ(LockerC.hardWareCheck(), HardWareStatus::ERROR);
}

TEST(LaboratoryTest, Test8){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    //Prepare mocks

    EXPECT_CALL(MockKeyPad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(1));

    EXPECT_CALL(MockLatch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(0));

    //Assert
    ASSERT_EQ(LockerC.hardWareCheck(), HardWareStatus::ERROR);
}

TEST(LaboratoryTest, Test9){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    PasswordResponse PRespone{
        PasswordResponse::Status::OK,
        "0000"
    };

    //Prepare mocks

    EXPECT_CALL(MockKeyPad, requestPassword)
            .Times(1)
            .WillOnce(Return(PRespone));

    //Assert
    ASSERT_TRUE(LockerC.isCorrectPassword());
}

TEST(LaboratoryTest, Test10){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    PasswordResponse PRespone{
        PasswordResponse::Status::OK,
        "1234"
    };

    //Prepare mocks

    EXPECT_CALL(MockKeyPad, requestPassword)
            .Times(1)
            .WillOnce(Return(PRespone));

    //Assert
    ASSERT_FALSE(LockerC.isCorrectPassword());
};

TEST(LaboratoryTest, Test11){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    PasswordResponse OldPasswordResponse{
        PasswordResponse::Status::OK,
        "0000"
    };

    PasswordResponse NewPasswordResponse{
        PasswordResponse::Status::OK,
        "1234"
    };

    //Prepare mocks
    EXPECT_CALL(MockKeyPad, requestPassword)
            .Times(3)
            .WillOnce(Return(OldPasswordResponse))
            .WillOnce(Return(NewPasswordResponse))
            .WillOnce(Return(NewPasswordResponse));

    //Act
    LockerC.resetPassword();

    //Assert
    ASSERT_TRUE(LockerC.isCorrectPassword());
}

TEST(LaboratoryTest, Test12){
    //Arrange
    MockIKeypad MockKeyPad;
    MockILatch MockLatch;
    LockController LockerC(&MockKeyPad, &MockLatch);

    PasswordResponse DefautPassword{
        PasswordResponse::Status::OK,
        "0000"
    };

    PasswordResponse UpdatedDefaultPassword{
        PasswordResponse::Status::OK,
        "9876"
    };

    PasswordResponse NewPassword{
        PasswordResponse::Status::OK,
        "1234"
    };

    //Prepare mocks
    EXPECT_CALL(MockKeyPad, requestPassword)
            .Times(5)
            .WillOnce(Return(DefautPassword))
            .WillOnce(Return(UpdatedDefaultPassword))
            .WillOnce(Return(UpdatedDefaultPassword))
            .WillOnce(Return(NewPassword))
            .WillOnce(Return(NewPassword));

    //Act
    LockerC.resetPassword();
    LockerC.resetPassword();
    //Assert
    ASSERT_TRUE(LockerC.isCorrectPassword());
}



#endif // TST_SOMETEST_H
