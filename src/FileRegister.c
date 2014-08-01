#include <stdio.h>
#include "FileRegister.h"
#include "ExecutionTable.h"
#include "Execute.h"


#define isInFirstAccessRange (address >= 0x00 && address <= 0x7f)
#define isInSecondAccessRange (address >= 0xf80 && address <= 0xfff)
#define isInBankedRange (address >= 0x80 && address <= 0xf79)
#define isInRangeOfBSR (fileRegisters[BSR] >= 0x0 && fileRegisters[BSR] <= 0x15)

unsigned char fileRegisters[4096];

int getFileRegData(int address, int access){
	int data;
	int getAddress;
	
	getAddress = findActualFileRegister(address, access);
	data = fileRegisters[getAddress];
	// printf("%x\n", data);
	
	return data;
}

int setFileRegData(int address, int access, int data){
	int getAddress;
	int newData;
	
	getAddress = findActualFileRegister(address, access);
	fileRegisters[getAddress] = data;
	newData = fileRegisters[getAddress];
	// printf("%x\n", newData);
	
	return newData;
	
}

int findActualFileRegister(int address, int access){
	int actualAddress;
	
	if(access == 0){
		if(isInFirstAccessRange || isInSecondAccessRange){
			return address;
		}else{
			address = address & 0xff;
			if(isInFirstAccessRange || isInSecondAccessRange){
				return address;
			}else{
				address = address + (0xf<<8);
			}
		}
	}else{
		if(isInRangeOfBSR){
			if(isInBankedRange){
				actualAddress = ((fileRegisters[BSR] & 0x0f)<<8) + (address & 0xff);
				return actualAddress;
			}else{
				actualAddress = ((fileRegisters[BSR] & 0x0f)<<8) + (address & 0xff);
				return actualAddress;
			}
		}else{
			actualAddress = ((fileRegisters[BSR] & 0x0f)<<8) + (address & 0xff);
			return actualAddress;
		}
	}
	
	return address;

}

void clearAllFileRegisters(){
	int i;
	
	for(i = 0; i < 4096; i++){
		fileRegisters[i] = 0;
	}
	
}