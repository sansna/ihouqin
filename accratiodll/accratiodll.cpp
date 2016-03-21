// AccRatio.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "accratiodll.h"

int INIT_STRGREEN(pstrGreen& pstr)
{
	pstr = (pstrGreen)malloc(sizeof(strGreen));
	pstr->cCode = (char*)malloc(cnLength);
	pstr->pNextGreen = NULL;
	return 0;
}

int INIT_STRBLUE(pstrBlue& pstr)
{
	pstr = (pstrBlue)malloc(sizeof(strBlue));
	pstr->cCode = (char*)malloc(cnLength);
	pstr->cName = (char*)malloc(cnNameMLen);
	pstr->cDate = (char*)malloc(cnDateLen);
	pstr->cDept = (char*)malloc(cnDeptLen);
	pstr->pNextBlue = NULL;
	return 0;
}

int INIT_STRCHART1(pstrChart1& pstr)
{
	pstr = (pstrChart1)malloc(sizeof(strChart1));
	pstr->cCode = (char*)malloc(cnLength);
	pstr->cName = (char*)malloc(cnDateLen);
	pstr->cDate = (char*)malloc(cnDateLen);
	pstr->cDept = (char*)malloc(cnDeptLen);
	pstr->nMark = 0;
	pstr->pNextChart1 = NULL;
	return 0;
}

int INIT_STRTRADE(pstrTrade& pstr)
{
	pstr = (pstrTrade)malloc(sizeof(strTrade));
	pstr->cCode = (char*)malloc(cnLength);
	pstr->cDept = (char*)malloc(cnDeptLen);
	pstr->nMark = 0;
	pstr->pNextTrade = NULL;
	return 0;
}

int INIT_STRCHART2(pstrChart2& pstr)
{
	pstr = (pstrChart2)malloc(sizeof(strChart2));
	pstr->cName = (char*)malloc(cnNameMLen);
	pstr->cDate = (char*)malloc(cnDateLen);
	INIT_STRTRADE(pstr->pstrTrd);
	pstr->pNextChart2 = NULL;
	return 0;
}

int INIT_STRCHART0(pstrChart0& pstr)
{
	pstr = (pstrChart0)malloc(sizeof(strChart0));
	pstr->cCode = (char*)malloc(cnLength);
	pstr->pNextChart0 = NULL;
	return 0;
}

int ADD_STRGREEN(pstrGreen& pstr, char* cC)
{
	strcpy_s(pstr->cCode,strlen(cC) + 1, (const char*)cC);
	pstrGreen pstrG;
	INIT_STRGREEN(pstrG);
	pstr->pNextGreen = pstrG;
	pstr = pstrG;

	return 0;
}

int IS_EXIST_STRBLUE(pstrBlue pstrbh, char* cC)
{
	while(pstrbh->pNextBlue != NULL)
	{
		if(!strcmp(cC,pstrbh->cCode))
			return 1;
		pstrbh = pstrbh->pNextBlue;
	}
	return 0;
}

int ADD_STRBLUE(pstrBlue& pstr, char* cC, char* cN, char* cD,char* cDept)
{
	strcpy_s(pstr->cCode, strlen(cC) + 1,cC);
	strcpy_s(pstr->cName, strlen(cN) + 1,cN);
	strcpy_s(pstr->cDate, strlen(cD) + 1,cD);
	strcpy_s(pstr->cDept, strlen(cDept) + 1, cDept);
	pstrBlue pstrB;
	INIT_STRBLUE(pstrB);
	pstr->pNextBlue = pstrB;
	pstr = pstrB;

	return 0;
}

int ADD_STRCHART0(pstrChart0& pstr, char* cC)
{
	pstrChart0 pstrT = (pstrChart0)malloc(sizeof(strChart0));
	pstrT->cCode = (char*)malloc(cnLength);
	strcpy_s(pstrT->cCode, strlen(cC) + 1,cC);
	pstrT->pNextChart0 = pstr;
	pstr = pstrT;
	return 0;
}

int PROC_DATE(char *cD)
{
	string szDate(cD);
	int nF = szDate.find_first_of('-');
	int nL = szDate.find_last_of('-');
	int nM = atoi(szDate.substr(nF + 1,nL-nF).c_str());
	int nD = atoi(szDate.substr(nL + 1,szDate.length()).c_str());
	ostringstream oszDate;
	oszDate<<szDate.substr(0,nF)<<'-';
	if(nM<10)
		oszDate<<'0'<<nM;
	else oszDate<<nM;
	oszDate<<'-';
	if(nD<10)
		oszDate<<'0'<<nD;
	else oszDate<<nD;
	strcpy_s(cD,oszDate.str().length() + 1,oszDate.str().c_str());

	return  0;
}

int ADD_STRCHART1(pstrChart1 pstrchead, pstrBlue pstrbhead)//用蓝表先写出CHART1，未标记
{
	do{
		strcpy_s(pstrchead->cCode, strlen(pstrbhead->cCode)+1,pstrbhead->cCode);
		strcpy_s(pstrchead->cName, strlen(pstrbhead->cName)+1,pstrbhead->cName);
		PROC_DATE(pstrbhead->cDate);
		strcpy_s(pstrchead->cDate, strlen(pstrbhead->cDate)+1,pstrbhead->cDate);
		pstrchead->cDate[10]='\0'; //cut date spec. to date.
		strcpy_s(pstrchead->cDept, strlen(pstrbhead->cDept)+1,pstrbhead->cDept);
		INIT_STRCHART1(pstrchead->pNextChart1);
		pstrchead = pstrchead->pNextChart1;
		pstrbhead = pstrbhead->pNextBlue;

	}while (pstrbhead->pNextBlue != NULL);
	return 0;
}

pstrChart1 FIND_CHART1BYCODE(pstrChart1 pstrc1h, char* cCode)//returns the pstr where cCode == cC
{
	while (pstrc1h->pNextChart1 != NULL)
	{
		if (! strcmp(cCode,pstrc1h->cCode))//equals
		{
			return pstrc1h;
		}
		pstrc1h = pstrc1h->pNextChart1;
	}
	return NULL;
}

int MDF_STRCHART1(pstrChart1 pstrc1h, pstrGreen pstrgh)//cC from strGreen, mdf nMark
{
	while(pstrgh->pNextGreen != NULL)
	{
		pstrChart1 pstrOffset = FIND_CHART1BYCODE(pstrc1h,pstrgh->cCode);
		if(pstrOffset)
			pstrOffset->nMark = 1;
		else{;}//not exist cC
		pstrgh = pstrgh->pNextGreen;
	}

	return 0;
}

ACCRATIODLL_API string TFILE_NAME_GEN(int nDate)
{
	int nY,nM,nD;
	nY = nDate/10000;
	nM = nDate%10000/100;
	nD = nDate%100;
	ostringstream oszDate;
	oszDate<<nY<<'-';
	if(nM<10)
		oszDate<<'0'<<nM;
	else
		oszDate<<nM;
	oszDate<<'-';
	if(nD<10)
		oszDate<<"0"<<nD;
	else
		oszDate<<nD;
	oszDate<<"t.csv";
	return oszDate.str();
}

int SZDATE_PROC(_IN_ char *cD, _OUT_ int& nT,_OUT_ int& nM,_OUT_ int &nK)
{
	char cT[5] = "";
	char cM[3] = "";
	char cK[3] = "";
	strncpy_s(cT,cD,4);
	nT = atoi(cT);
	strncpy_s(cM,cD + 5,2);
	nM = atoi(cM);
	strncpy_s(cK,cD + 8,2);
	nK = atoi(cK);
	if(nT&&nM&&nK)
		return 0;
	return 1;
}

ACCRATIODLL_API int FILE_NAME_INT(char * cD)
{
	int nY,nM,nD;
	SZDATE_PROC(cD,nY,nM,nD);
	return nY*10000 + nM*100 + nD;
}

int SZDATE_COMPARE(char* cD)
{
	int nT=0;
	int nM = 0;
	int nK = 0;
	SZDATE_PROC(cD,nT,nM,nK);
	if(nT * 12 + nM < DateBenchmark)
		return -1;
	else if(nT * 12 + nM > DateBenchmark)
		return 1;
	else if (nK != 1)
		return 1;

	return 0;
}

int SZDATE_YESTERDAY(_IN_ char* cD, _OUT_ char*cDy)
{
	int nT = 0;
	int nM = 0;
	int nK = 0;
	SZDATE_PROC(cD,nT,nM,nK);
	if(nK > 1)
		nK --;
	else if(nM == 1)
	{
		nT --;
		nM = 12;
		nK = 30;
	}
	else
	{
		nM --;
		switch(nM)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			nK = 31;
		case 2:
			if(nT%4==0 && nT%40!=0 || nT%400==0)
				nK = 29;
			else
				nK = 28;
		default:
			nK = 30;
		}
	}
	ostringstream szY;
	if(nT < 10)
		szY<<'0'<<nT;
	else
		szY<<nT;
	szY<<'-';
	if(nM < 10)
		szY<<'0'<<nM;
	else
		szY<<nM;
	szY<<'-';
	if(nK < 10)
		szY<<'0'<<nK;
	else
		szY<<nK;
	strcpy_s(cDy,szY.str().length() + 1,szY.str().c_str());
	return 0;
}

int READ_STRCHART0(_IN_ char *cDate, _OUT_ pstrChart0& pstrc0h)
{
	FILE *pFile;
	errno_t ferr = 0;
	char *cDir = (char*)malloc(_MAX_PATH);
	string szDir(".\\arbackup\\");
	szDir.append(cDate).append("b.csv");
	ferr = fopen_s(&pFile,szDir.c_str(),"rb");
	if(ferr)
	{
		//cout<<"file read error:"<<cDate<<endl;
		//system("pause");
		//exit(ferr);
		return 2;
	}
	char * cCode = (char*)malloc(cnLength);
	INIT_STRCHART0(pstrc0h);
	while(!feof(pFile))
	{
		fscanf_s(pFile,"%s ",cCode,cnLength);
		ADD_STRCHART0(pstrc0h,cCode);
	}

	fclose(pFile);
	return 0;
}

int DEL_STRCHART0(pstrChart0 pstr)
{
	strcpy_s(pstr->cCode,strlen(pstr->pNextChart0->cCode) + 1,pstr->pNextChart0->cCode);

	pstrChart0 pstrT = pstr->pNextChart0;
	pstr->pNextChart0 = pstr->pNextChart0->pNextChart0;
	free(pstrT);
	return 0;
}

int DEL_STRCHART1(pstrChart1 pstr)
{
	strcpy_s(pstr->cCode,strlen(pstr->pNextChart1->cCode) + 1,pstr->pNextChart1->cCode);
	strcpy_s(pstr->cDate,strlen(pstr->pNextChart1->cDate) + 1,pstr->pNextChart1->cDate);
	strcpy_s(pstr->cDept,strlen(pstr->pNextChart1->cDept) + 1,pstr->pNextChart1->cDept);
	strcpy_s(pstr->cName,strlen(pstr->pNextChart1->cName) + 1,pstr->pNextChart1->cName);
	pstr->nMark = pstr->pNextChart1->nMark;

	pstrChart1 pstrT = pstr->pNextChart1;
	pstr->pNextChart1 = pstr->pNextChart1->pNextChart1;
	free(pstrT);
	return 0;
}

int MDF_STRCHART1_WITH_STRCHART0(pstrChart1 pstrc1h, pstrChart0& pstrc0h, char* cD)
{
	if(SZDATE_COMPARE(cD) <= 0)
	{
		INIT_STRCHART0(pstrc0h);
		return 0;
	}
	char cDy[11];
	SZDATE_YESTERDAY(cD,cDy);
	pstrChart0 pstrc0 = NULL;
	if(READ_STRCHART0(cDy,pstrc0h))//初始化表0并生成表0
		return 2;
	pstrc0 = pstrc0h;
	while(pstrc0->pNextChart0 != NULL)
	{
		pstrChart1 pstrc1Offset = FIND_CHART1BYCODE(pstrc1h, pstrc0->cCode);
		if(pstrc1Offset)
		{
			if(pstrc1Offset->nMark == 1)
			{
				//delete from c1 & c0 where cCode matches
				DEL_STRCHART0(pstrc0);
				DEL_STRCHART1(pstrc1Offset);
				if(pstrc0->pNextChart0 == NULL)
					break;
			}
			else if(pstrc1Offset->nMark == 0)
			{
				//delete from c1 where cCode matches
				DEL_STRCHART1(pstrc1Offset);
			}
		}
		pstrc0 = pstrc0->pNextChart0;
	}

	return 0;
}

int WRITE_FILE_STRCHART0(pstrChart0& pstrc0h, pstrChart1 pstrc1h)
{
	string szDir(".\\arbackup\\");
	szDir.append(pstrc1h->cDate).append("b.csv");
	//add strchart0 with strchart1 where nMark == 0
	while(pstrc1h->pNextChart1 != NULL)
	{
		if(pstrc1h->nMark == 0)
			ADD_STRCHART0(pstrc0h,pstrc1h->cCode);
		pstrc1h = pstrc1h->pNextChart1;
	}
	//write file
	pstrChart0 pstrc0 = pstrc0h;

	ofstream outfile(szDir.c_str());
	if(!outfile.is_open())
		//exit(14);
		return 1;
	while(pstrc0->pNextChart0 != NULL)
	{
		outfile<<pstrc0->cCode<<endl;
		pstrc0 = pstrc0->pNextChart0;
	}
	outfile.close();
	return 0;
}

int ADD_STRTRADE(pstrTrade& pstr, char* cCode, char* cDept, int nMark)//插入trade pstr取地址
{
	pstrTrade pstrT = (pstrTrade)malloc(sizeof(strTrade));
	pstrT->cCode = (char*)malloc(cnLength);
	pstrT->cDept = (char*)malloc(cnDeptLen);
	strcpy_s(pstrT->cCode, strlen(cCode) + 1,(const char*)cCode);
	strcpy_s(pstrT->cDept, strlen(cDept) + 1,(const char*)cDept);
	pstrT->nMark = nMark;
	pstrT->pNextTrade = pstr;
	pstr = pstrT;

	return 0;
}

int judy(char* cD)
{
	char cT[5] = "";
	int nT=0;
	int judge = 0;
	strncpy_s(cT,cD,4);
	nT = atoi(cT);
	if(nT > 2019)
		judge ++;
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int year = aTime->tm_year + 1900;
	if(year >= 2019)
		judge ++;
	if(judge > 1)
		//exit(0);
		return 1;
	return 0;

}

int ADD_STRCHART2(pstrChart2 pstrc2h, pstrChart1 pstrc1h)//用 CHART1换算CHART2 一步完成
{
	char *cC,*cN,*cD,*cDept;
	cC = (char*)malloc(cnLength);
	cN = (char*)malloc(cnNameMLen);
	cD = (char*)malloc(cnDateLen);
	cDept = (char*)malloc(cnDeptLen);
	pstrChart2 pstrc2 = NULL;
	while(pstrc1h->pNextChart1 != NULL)
	{
		pstrc2 = pstrc2h;
		strcpy_s(cC,strlen(pstrc1h->cCode) + 1,pstrc1h->cCode);
		strcpy_s(cN,strlen(pstrc1h->cName) + 1,pstrc1h->cName);
		strcpy_s(cD,strlen(pstrc1h->cDate) + 1,pstrc1h->cDate);
		strcpy_s(cDept,strlen(pstrc1h->cDept) + 1,pstrc1h->cDept);
		judy(cD);
		while( (strcmp(cN,pstrc2->cName)) /*|| (strcmp(cD,pstrc2->cDate))*/)
		{
			if(pstrc2->pNextChart2 == NULL) break;
			pstrc2 = pstrc2->pNextChart2;
		}
		if(pstrc2->pNextChart2 == NULL)
		{
			strcpy_s(pstrc2->cDate, strlen(cD) + 1,(const char*)cD);
			strcpy_s(pstrc2->cName, strlen(cN) + 1,(const char*)cN);
			ADD_STRTRADE(pstrc2->pstrTrd,cC,cDept,pstrc1h->nMark);
			INIT_STRCHART2(pstrc2->pNextChart2);
		}
		else{
			ADD_STRTRADE(pstrc2->pstrTrd,cC,cDept,pstrc1h->nMark);
		}

		pstrc1h = pstrc1h->pNextChart1;
	}
	free(cC);
	free(cD);
	free(cN);

	return 0;
}

int COUNT_STRCHART2_STRTRADE_NUMBERS(pstrChart2 pstrc2, int& nTotal, int& nNotScanned, string& szUnScanned)//output nTotal, nNotScanned
{
	nTotal = 0, nNotScanned = 0;
	pstrTrade pstrT = pstrc2->pstrTrd;
	while(pstrT->pNextTrade != NULL)
	{
		nTotal ++;
		if(pstrT->nMark == 0)
		{
			nNotScanned ++;
			szUnScanned.append(pstrT->cCode).append(";");
		}
		pstrT = pstrT->pNextTrade;
	}
	return 0;
}

int IS_DUPLICATE_GREEN(pstrGreen pstrgh, char* cCode)
{
	while(pstrgh->pNextGreen != NULL)
	{
		if(!strcmp(pstrgh->cCode,cCode))
			return 1;
		pstrgh = pstrgh->pNextGreen;
	}
	return 0;
}

int IS_DUPLICATE_BLUE(pstrBlue pstrbh, char* cCode)
{
	while(pstrbh->pNextBlue != NULL)
	{
		if(!strcmp(pstrbh->cCode,cCode))
			return 1;
		pstrbh = pstrbh->pNextBlue;
	}
	return 0;
}

int READ_FILE(string str, pstrBlue& pstrbh,pstrGreen& pstrgh)
{
	FILE *pFile;
	errno_t ferr = 0;
	
	if(str.length()>=5)
	{
		ferr = fopen_s(&pFile,str.c_str(),"rb");
	}
	else
	{
		return 3;
	}
	if (ferr)
	{
		//printf("File open error.\n");
		//exit(12);
		return 1;
	}
	//start insert
	pstrBlue pstrblue;
	pstrGreen pstrgreen;
	INIT_STRBLUE(pstrblue);
	pstrbh = pstrblue;
	INIT_STRGREEN(pstrgreen);
	pstrgh = pstrgreen;
	char* lpstrTemp = (char*)malloc(cnLength + cnDateLen + cnNameMLen + cnDeptLen);
	char *cCode,*cName,*cDate, *cDept;
	cCode = (char*)malloc(cnLength);
	cName = (char*)malloc(cnNameMLen);
	cDate = (char*)malloc(cnDateLen);
	cDept = (char*)malloc(cnDeptLen);
	while(!feof(pFile))
	{
		fscanf_s(pFile,"%[^\r]\r",lpstrTemp,cnLength + cnDateLen + cnNameMLen);
		int nLen = strlen(lpstrTemp);
		if(nLen == (cnGWCCount * 2 + cnGItemNum - 1) || nLen == (cnBWCCount * 2 + cnBItemNum - 1))//标题忽略
			continue;
		if( nLen <= (cnLength + 3))//green
		{
			_fseeki64(pFile, (-1)*nLen - 2, SEEK_CUR);
			fscanf_s(pFile,"%s ",cCode,cnLength-1);
			if(!IS_DUPLICATE_GREEN(pstrgh,cCode))
				ADD_STRGREEN(pstrgreen,cCode);
		}
		else {//blue
			fseek(pFile, (-1)*nLen - 2, SEEK_CUR);
			fscanf_s(pFile,"%[^,],%[^,],%[^,],%[^\r]\r",cCode,cnLength-1,cName,cnNameMLen-1,cDept,cnDeptLen-1,cDate,cnDateLen-1);
			if(!IS_DUPLICATE_BLUE(pstrbh,cCode))
				ADD_STRBLUE(pstrblue,cCode,cName,cDate,cDept);
		}
	}
	free(lpstrTemp);
	fclose(pFile);
	free(cCode);
	free(cDate);
	free(cName);
	free(cDept);

	//cout<<"Reading ok.. Now processing.."<<endl;

	return 0;
}

ACCRATIODLL_API string WSTR_TO_UTF8(const wchar_t *lpwstrSrc,int nLength)
{
	int nSize = ::WideCharToMultiByte(
		CP_UTF8,
		0,
		lpwstrSrc,
		nLength,
		NULL,
		0,
		NULL,
		NULL);
	if(nSize == 0)
		return "";
	string szBuffer;
	szBuffer.resize(nSize);
	::WideCharToMultiByte(
		CP_UTF8,
		0,
		lpwstrSrc,
		nLength,
		const_cast<char*>(szBuffer.c_str()),
		nSize,
		NULL,
		NULL);
	return szBuffer;
}

ACCRATIODLL_API string WSTR_TO_UTF8(wstring &wszSrc)
{
	return WSTR_TO_UTF8((const wchar_t *)wszSrc.c_str(),(int)wszSrc.size());
}

int FOUTPUT_STRCHART2(char* cDate,pstrChart2 pstrc2h)
{
	string szDir(".\\arresult\\");
	szDir.append(cDate).append("t.csv");
	ofstream outfile(szDir.c_str());
	if (!outfile.is_open())	
	{
		//cout<<"arresult error."<<endl;
		//exit(13);
		return 1;
	}

	string szUnScanned;
	int nT,nN;
	nT = nN = 0;
	wstring wszTitle(L"姓名,运单总数,运单未签收,运单完成率,未完成订单\n");
	outfile<<WSTR_TO_UTF8(wszTitle);
	while(pstrc2h->pNextChart2 != NULL)
	{
		szUnScanned.clear();
		COUNT_STRCHART2_STRTRADE_NUMBERS(pstrc2h,nT,nN,szUnScanned);
		double i = (nT-nN)*1.0/nT*100;//pstrc2h->cName
		int nWCSize = ::MultiByteToWideChar(
			CP_ACP,
			0,
			pstrc2h->cName,
			strlen(pstrc2h->cName),
			NULL,
			0
			);
		wstring wszName;
		wszName.resize(nWCSize);
		::MultiByteToWideChar(
			CP_ACP,
			0,
			pstrc2h->cName,
			strlen(pstrc2h->cName),
			(wchar_t*)(wszName.c_str()),
			nWCSize
			);
		outfile<<WSTR_TO_UTF8(wszName)<<","<<nT<<","<<nN<<","<<setprecision(4)<<i<<"%"<<","<<szUnScanned.c_str()<<endl;
		pstrc2h = pstrc2h->pNextChart2;
	}
	outfile.close();
	return 0;
}



ACCRATIODLL_API int AR(string str)
{
	pstrBlue pstrbh = NULL;//派件表
	pstrGreen pstrgh = NULL;//签收表
	pstrChart0 pstrc0h = NULL;//核对表
	pstrChart1 pstrc1h = NULL;//整合表
	pstrChart2 pstrc2h = NULL;//结果表
	int nReadResult = READ_FILE(str,pstrbh,pstrgh);
	if(nReadResult == 1)//初始化派件签收表
		return 1;
	else if(nReadResult == 3)
		return 3;
	INIT_STRCHART1(pstrc1h);//初始化整合表
	ADD_STRCHART1(pstrc1h,pstrbh);//生存整合表
	MDF_STRCHART1(pstrc1h,pstrgh);//修改1
	if(MDF_STRCHART1_WITH_STRCHART0(pstrc1h,pstrc0h,pstrc1h->cDate))//修改2，初始化并生成核对表
		return 2;
	WRITE_FILE_STRCHART0(pstrc0h,pstrc1h);//修改整合表、核对表并将其写入文件备份
	INIT_STRCHART2(pstrc2h);//初始化结果表
	ADD_STRCHART2(pstrc2h,pstrc1h);//根据整合表变形出结果表
	FOUTPUT_STRCHART2(pstrc1h->cDate,pstrc2h);//根据结果表计算并输出文件结果
	return FILE_NAME_INT(pstrbh->cDate);
}

ACCRATIODLL_API int AR_COUNT()
{
	
}

