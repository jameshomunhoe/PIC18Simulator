#include <stdio.h>
#include "ExecutionTable.h"
#include "Execute.h"



ExecutionTable executionTable[64] = {
	[0x06] = executeSWAPF,
	[0x0e] = executeXORWF,
	[0x16] = executeSUBWFB,
	[0x17] = executeSUBWF,
	[0x19] = executeTSTFSZ,
	[0x1c] = executeBTG,
	[0x1d] = executeBTG,
	[0x1e] = executeBTG,
	[0x1f] = executeBTG,
	[0x20] = executeBSF,
	[0x21] = executeBSF,
	[0x22] = executeBSF,
	[0x23] = executeBSF,
	[0x24] = executeBCF,
	[0x25] = executeBCF,
	[0x26] = executeBCF,
	[0x27] = executeBCF,
	[0x28] = executeBTFSS,
	[0x29] = executeBTFSS,
	[0x2a] = executeBTFSS,
	[0x2b] = executeBTFSS,
	[0x2c] = executeBTFSC,
	[0x2d] = executeBTFSC,
	[0x2e] = executeBTFSC,
	[0x2f] = executeBTFSC,
	[0x34] = executeBRA,
	[0x35] = executeBRA,
	[0x38] = executeConditionalBranch,
	[0x39] = executeConditionalBranch,
	[0x3a] = executeConditionalBranch,
	[0x3b] = executeConditionalBranch,
	[0x1b] = executeMOVWForNEGF,
	[0x0d] = executeRLCF,
	[0x10] = executeRRNCF,
	[0x09] = executeADDWF

};

