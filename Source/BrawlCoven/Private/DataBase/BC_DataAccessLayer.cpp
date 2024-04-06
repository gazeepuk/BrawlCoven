// Ivan Piankouski / GazeePuk


#include "DataBase/BC_DataAccessLayer.h"

#include "PreparedStatementManager.h"

void UBC_DataAccessLayer::Build(FString DatabaseFilePath, FGameDbConfig Config)
{
	QueryManager->LoadStatements();
}
