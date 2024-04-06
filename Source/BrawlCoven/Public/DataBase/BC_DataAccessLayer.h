// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "DbBase.h"
#include "BC_DataAccessLayer.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_DataAccessLayer : public UDbBase
{
	GENERATED_BODY()
		public:
	/*int32 GetUserIdByLogin(const FString& InUserId) const;
	int32 CreateUserAccount(const FString& InEmail, const FString& InLogin, const FString& InHashPassword,
	                        const FString& InDisplayName, const int8
	                        & InbAdmin) const;
	int32 LoginUserAccount(const FString& InUserLogin, const FString& InPassword) const;
	bool ChangeUserPassword(const FString& InUserId, const FString& InOldPassword, const FString& InNewPassword) const;
	bool DeleteUserAccount(const FString& InUserLogin, const FString& InHashPassword) const;
	bool DeleteUserAccount(const FString& InUserLogin) const;
	FString ChangeUserDisplayName(const FString& InUserId, const FString& InNewUserDisplayName) const;
	int32 AddUserTaskRecord(const FString& InUserId, const FString& InTaskId, const FString& InUserBestResult) const;
	int32 GetUserTaskBestResult(const FString& InUserId, const FString& InTaskId) const;
	bool AddUserAchievement(const FString& InUserId, const FString& InAchievementId) const;*/
private:
	virtual void Build(FString DatabaseFilePath, FGameDbConfig Config) override;

	FString Q_CreateUserAccount = "CreateUserAccount";
	FString Q_LoginUserAccount = "LoginUserAccount";
	FString Q_ChangeUserAccount = "ChangeUserPassword";
	FString Q_DeleteUserAccount = "DeleteUserAccount";
	FString Q_ChangeUserDisplayName = "ChangeUserDisplayName";
	FString Q_GetUserIdByLogin = "GetUserIdByLogin";
	FString Q_AddUserAchievement = "AddUserAchievement";
	
	const FString P_User_Id = TEXT("@user_id");
	const FString P_User_Email = TEXT("@user_email");
	const FString P_User_Login = TEXT("@user_login");
	const FString P_User_HashPassword = TEXT("@user_hashPassword");
	const FString P_User_DisplayName = TEXT("@user_displayName");
	const FString P_Achievement_Id = TEXT("@achievement_id");
};
