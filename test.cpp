#include <gtest/gtest.h>
#include "cmd.h"
#include "cmd.cpp"


TEST(NotValidCommand, NotValidCommandTest) {
	Dictionary dir;
  EXPECT_EQ(false, dir.validcommand("notvalid"));
  EXPECT_TRUE(true);
}

TEST(ValidCommand, ValidCommandTest) {
	Dictionary dir;
	EXPECT_EQ(true, dir.validcommand("mkdir"));
	EXPECT_TRUE(true);
}

TEST(NotValidSplit, NotValidSplitTest) {
	Dictionary dir;
	string goodOutput = dir.splitCurrentFolder("Fomappa/Mappa");
	EXPECT_EQ("Fomappa", goodOutput);
	EXPECT_TRUE(true);
}

TEST(ValidSplit, ValidSplitTest) {
	Dictionary dir;
	string goodOutput = dir.splitCurrentFolder("Fomappa/Mappa/Mappacska/Mappaharom/Megtobbmappa");
	EXPECT_NE("Fomappa", goodOutput);
	EXPECT_TRUE(true);
}


TEST(ValidCDFolderMkdir, ValidCDTestMkdir) {
	Dictionary dir;
	string dirName = "Mappa";
	string currentFolder = "Fomappa";
	dir.mkdir(dirName, currentFolder);
	string goodOutput = dir.cd(dirName,currentFolder);
	EXPECT_EQ("Fomappa/Mappa", goodOutput);
	EXPECT_TRUE(true);
}

TEST(ValidCDFolderNofolder, ValidCDTestNofolder) {
	Dictionary dir;
	string dirName = "Mappa";
	string currentFolder = "Fomappa";
	dir.mkdir(dirName, currentFolder);
	string goodOutput = dir.cd(dirName, currentFolder);
	EXPECT_NE("Fomappa/NemletezoMappa", goodOutput);
	EXPECT_TRUE(true);
}

TEST(ValidCD, ValidCDTest) {
	Dictionary dir;
	string dirName = "Mappa";
	string currentFolder = "Fomappa";
	string goodOutput = dir.cd(dirName, currentFolder);	
	EXPECT_EQ("Fomappa", goodOutput);
	EXPECT_TRUE(true);
}

TEST(ListFolders, ListFoldersTest) {
	Dictionary dir;
	CaptureStdout();	
	string dirName = "Mappa";
	string dirName2 = "Mappa2";
	string expectedOutput = "Mappa\nMappa2\n";
	string currentFolder = "Fomappa";
	dir.mkdir(dirName, currentFolder);
	dir.mkdir(dirName2, currentFolder);
	dir.ls(currentFolder);
	string output = GetCapturedStdout();
	EXPECT_EQ(expectedOutput, output);
	EXPECT_TRUE(true);
}

TEST(FolderExistsError, FolderExistsErrorTest) {
	Dictionary dir;
	testing::internal::CaptureStdout();
	string dirName = "Mappa";
	string dirName2 = "Mappa";
	string expectedOutput = "This file/directory already exists\n";
	string currentFolder = "Fomappa";
	dir.mkdir(dirName, currentFolder);
	dir.mkdir(dirName2, currentFolder);
	string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expectedOutput, output);
	EXPECT_TRUE(true);
}

TEST(ValidRemoveList, ValidRemoveListTest) {
	Dictionary dir;
	testing::internal::CaptureStdout();
	string dirName = "Mappa";
	string dirName2 = "Mappa2";
	string expectedOutput = "Mappa\n";
	string currentFolder = "Fomappa";
	dir.mkdir(dirName, currentFolder);
	dir.mkdir(dirName2, currentFolder);
	dir.rm(dirName2, currentFolder);
	dir.ls(currentFolder);
	string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expectedOutput, output);
	EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
