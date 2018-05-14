#include "hw3.h"

/*
	Adam Gincel - agincel
	hw3.c

	I pledge my honor that I have abided by the Stevens Honor System.
*/

using namespace std;
int pageID = 0, accessOperations = 0, pageFaults;

int diskSize, blockSize;

int getDiskSize()
{
	return diskSize;
}

int getBlockSize()
{
	return blockSize;
}


int main(int argc, char** argv)
{
	if (argc != 5) //wrong usage
	{
		cout << "usage: ./hw3 file_list dir_list disk_size block_size\n";
		return 1;
	}

	diskSize = atoi(argv[3]);
	blockSize = atoi(argv[4]);

	ifstream dirList, fileList;
	dirList.open(argv[2]); //give it the file plist
	string currentLine;
	vector<string> directories;
	vector<string> fileInfo;

	G_Node *myRoot = new G_Node(".", false);
	G_Node *currentNode;
	G_Node *targetNode;
	if(!dirList)
		error("Invalid dirList file.\n");
	dirList >> currentLine;
	while(!dirList.eof() && dirList.is_open()) //load directories
	{
		dirList >> currentLine;
		directories = splitByCharacter(currentLine, '/');
		currentNode = myRoot;
		for(int i = 1; i < directories.size(); i++) //for each directory after .
		{
			if(getNodeByName(currentNode->children, directories[i]) == NULL) //directory doesn't currently exist
			{
				currentNode->addChild(new G_Node(directories[i], false));
			}
			targetNode = getNodeByName(currentNode->children, directories[i]);
			if(targetNode != 0)// is valid directory, should always be
			{
				currentNode = targetNode;
			}
			else
				error("ERROR: Invalid directory after initializing it?\n");
		}
	}

	fileList.open(argv[1]);
	if(!fileList)
		error("Invalid file_list file\n");

	int blocksNeeded = ceil(double(diskSize) / double(blockSize));
	L_Node *diskSpace = new L_Node(0, blocksNeeded);

	int count = 0;
	while(!fileList.eof() && fileList.is_open()) //load files into directories
	{
		getline(fileList, currentLine);
		fileInfo = splitByCharacter(currentLine, ' ');
		//printVector(fileInfo);
		if(fileInfo.size() > 0)
		{
			directories = splitByCharacter(fileInfo[fileInfo.size() - 1], '/');
			//printVector(directories);
			fileInfo.clear();
			currentNode = myRoot;
			for(int i = 1; i < directories.size() - 1; i++) //drill down to folder
			{
				targetNode = getNodeByName(currentNode->children, directories[i]);
				if(targetNode != 0) //is valid directory, should be
				{
					currentNode = targetNode;
				}
				else
					error("ERROR: Putting File in directory that doesn't exist\n");
			}
			//we should now be at our folder
			G_Node *newFile = new G_Node(directories[directories.size() - 1], true);
			currentNode->addChild(newFile);
			newFile->addFileInfo(atoi(fileInfo[6].c_str())); //tell file how many bytes it needs
			for(int i = 0; i < getBlocksNeeded(newFile->bytesNeeded); i++)
			{
				int blockTaken = consumeBlock(diskSpace);
				if(blockTaken == -1)
					error("Ran out of disk space in file directory load!");
				//printLNodes(diskSpace);
				if(newFile->fileSpace == 0)
					newFile->fileSpace = new F_Node(blockTaken);
				else
					newFile->fileSpace->addToEnd(blockTaken);
			}
		}
	}
	//printLNodes(diskSpace);
	//printDirectory(myRoot);
	currentLine = "";
	currentNode = myRoot;
	vector<string> typedCommands;
	//TIME TO ACCEPT USER INPUT
	while(currentLine.compare("exit") != 0) //while the user hasn't typed exit
	{
		currentLine = "";
		cout << currentNode->getPath() << "$ ";
		getline(cin, currentLine);

		if(currentLine.compare("") != 0) //we were given a command
		{
			typedCommands = splitByCharacter(currentLine, ' ');
			if(typedCommands[0].compare("cd") == 0)
			{
				if(typedCommands.size() > 1) //there's a destination
				{
					//supporting cd .. for no reason lol
					if(typedCommands[1].compare("..") == 0 || typedCommands[1].compare("../") == 0)
					{
						if(currentNode->parent != 0)
							currentNode = currentNode->parent;
					}
					else
					{
						G_Node *destination = getNodeByName(currentNode->children, typedCommands[1]);
						if(destination != 0 && !destination->isFile) //found a place to go
						{
							currentNode = destination;
						}
						else
						{
							cout << "error: cd: could not find folder \'" << typedCommands[1] << "\'\n";
						}
					}
				}
				else
				{
					cout << "error: cd: need a destination.\n";
				}
			}
			else if(typedCommands[0].compare("cd..") == 0)
			{
				if(currentNode->parent != 0)
				{
					currentNode = currentNode->parent;
				}
			}
			else if(typedCommands[0].compare("ls") == 0)
			{
				for(int i = 0; i < currentNode->children.size(); i++) //print all folders, with / at end
					if(!currentNode->children[i]->isFile)
						cout << currentNode->children[i]->name << "/ ";
				for(int i = 0; i < currentNode->children.size(); i++) //print all files
					if(currentNode->children[i]->isFile)
						cout << currentNode->children[i]->name << " ";
				cout << "\n";
			}
			else if (typedCommands[0].compare("mkdir") == 0)
			{
				if(typedCommands.size() > 1) //typed a name
				{
					if(getNodeByName(currentNode->children, typedCommands[1]) == 0)
						currentNode->addChild(new G_Node(typedCommands[1], false));
					else
						cout << "error: mkdir: name \'" << typedCommands[1] << "\' already in use\n";
				}
			}
			else if(typedCommands[0].compare("create") == 0)
			{
				if(typedCommands.size() > 1) //typed name
				{
					if(getNodeByName(currentNode->children, typedCommands[1]) == 0)
					{
						G_Node *newFile = new G_Node(typedCommands[1], true);
						currentNode->addChild(newFile);
						newFile->addFileInfo(0);
					}
					else
						cout << "error: create: name \'" << typedCommands[1] << "\' already in use\n";
					
				}
			}
			else if(typedCommands[0].compare("append") == 0)
			{
				if(typedCommands.size() > 2) //append file bytes
				{
					G_Node *targetNode = getNodeByName(currentNode->children, typedCommands[1]);
					if(targetNode != 0 && targetNode->isFile) //target node exists, and is file
					{
						targetNode->bytesNeeded += atoi(typedCommands[2].c_str());
						//cout << "Time to run getBlocksNeeded, blocksPossessed, and getFreeBlocks\n";
						if(getBlocksNeeded(targetNode->bytesNeeded) - targetNode->blocksPossessed() > diskSpace->getFreeBlocks()) //need more blocks than exist
							cout << "error: append: Not enough disk space for that operation.\n";
						else
						{
							//cout << "Blocks to claim: " << getBlocksNeeded(targetNode->bytesNeeded) - targetNode->blocksPossessed() << endl;
							int toClaim = getBlocksNeeded(targetNode->bytesNeeded) - targetNode->blocksPossessed();
							for(int i = 0; i < toClaim; i++)
							{
								//cout << "Going to take block...";
								int blockTaken = consumeBlock(diskSpace);
								//cout << "done.\n";
								if(blockTaken == -1)
								{
									cout << "Ran out of space mid append. This shouldn\'t have happened...\n";
								}
								else
								{
									if(targetNode->fileSpace == 0)
										targetNode->fileSpace = new F_Node(blockTaken);
									else
										targetNode->fileSpace->addToEnd(blockTaken);
								}
							}
						}
					}
				}
			}
			else if(typedCommands[0].compare("remove") == 0) //this involves deleting blocks
			{
				if(typedCommands.size() > 2) //delete file bytes
				{
					G_Node *targetNode = getNodeByName(currentNode->children, typedCommands[1]);
					if(targetNode != 0 && targetNode->isFile)
					{
						targetNode->bytesNeeded -= atoi(typedCommands[2].c_str());
						if(targetNode->bytesNeeded < 0)
							targetNode->bytesNeeded = 0;
						int toRemove = targetNode->blocksPossessed() - getBlocksNeeded(targetNode->bytesNeeded);
						for(int i = 0; i < toRemove; i++)
						{
							int blockFreed = removeBlock(diskSpace, targetNode->fileSpace->getEndValue());
							if(blockFreed >= 0)
							{
								targetNode->fileSpace->deleteEnd();
							}
							else
							{
								break;
							}
						}
						if(getBlocksNeeded(targetNode->bytesNeeded) == 0)
						{
							targetNode->fileSpace = (F_Node *)0;
						}
					}
				}
			}
			else if (typedCommands[0].compare("delete") == 0) //this also invovles deleting blocks
			{
				if(typedCommands.size() > 1)
				{
					G_Node *targetNode = getNodeByName(currentNode->children, typedCommands[1]);
					if(targetNode != 0 && targetNode->isFile)
					{
						targetNode->bytesNeeded = 0;
						int toRemove = targetNode->blocksPossessed();
						for(int i = 0; i < toRemove; i++)
						{
							int blockFreed = removeBlock(diskSpace, targetNode->fileSpace->getEndValue());
							if(blockFreed >= 0)
								targetNode->fileSpace->deleteEnd();
							else
								break;
						}
						targetNode->fileSpace = (F_Node *)0;
						int indexToDelete = getNodeIndexByName(currentNode->children, typedCommands[1]);
						delete(currentNode->children[indexToDelete]);
						currentNode->children.erase(currentNode->children.begin() + indexToDelete);
					}
					else if(targetNode != 0 && !targetNode->isFile)
					{
						if(targetNode->children.size() == 0) //can delete empty folder
						{
							int indexToDelete = getNodeIndexByName(currentNode->children, typedCommands[1]);
							delete(currentNode->children[indexToDelete]);
							currentNode->children.erase(currentNode->children.begin() + indexToDelete);
						}
						else
						{
							cout << "error: delete: unable to delete non-empty folder \'" << typedCommands[1] << "\'\n";
						}
					}
					else
						cout << "error: delete: \'" << typedCommands[1] << "\' not found\n";
				}
			}
			else if (typedCommands[0].compare("dir") == 0)
			{
				printDirectory(currentNode);
			}
			else if (typedCommands[0].compare("prfiles") == 0)
			{
				for(int i = 0; i < currentNode->children.size(); i++) //print all files
					if(currentNode->children[i]->isFile)
						cout << currentNode->children[i]->name << " | " << currentNode->children[i]->bytesNeeded << " | " << currentNode->children[i]->blocksPossessed() << endl;
			}
			else if (typedCommands[0].compare("prdisk") == 0)
			{
				printLNodes(diskSpace);
			}

		}
	}
	return 0;
}
