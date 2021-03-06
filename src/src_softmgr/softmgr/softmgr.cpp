// softmgr.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "SoftChecker.h"
#include "SoftManager.h"
#include "DTManager.h"
#include <libdownload/libDownload.h>
#include "SoftMgrUpdateHelper.h"
#include "SoftUninstall.h"
#include "SoftInfoQuery.h"
#include <softmgr/ISoftUninstall.h>
#include "SoftInstall.h"
using namespace ksm;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

CSoftManager g_sm;

CSoftChecker g_sc;

HRESULT WINAPI CreateUpdateHelper( REFIID riid, void** ppvObj )
{
	ATLASSERT(ppvObj);
//	__asm int 3;
	if ( IsEqualIID(riid, __uuidof(IUpdateHelper)) )
	{
		IUpdateHelper *p = new CSoftMgrUpdateHelper;
		p->AddRef();

		*ppvObj = p;
		return S_OK;
	}
	return E_NOINTERFACE;
}

HRESULT CreateSoftMgrObject( REFIID riid, void** ppvObj )
{
	ATLASSERT(ppvObj);
	if ( IsEqualIID(riid, __uuidof(ISoftChecker)) )
	{
		ISoftChecker *p = &g_sc;
		*ppvObj = p;
		return S_OK;
	}
	if ( IsEqualIID(riid, __uuidof(ISoftCheckerEx)) )
	{
		ISoftCheckerEx *p = &g_sc;
		*ppvObj = p;
		return S_OK;
	}
	if ( IsEqualIID(riid, __uuidof(ISoftManager)) )
	{
		ISoftManager *p = &g_sm;
		*ppvObj = p;
		return S_OK;
	}
	if ( IsEqualIID(riid, __uuidof(IDTManager)) )
	{
		IDTManager *p = new CDTManager;
		*ppvObj = p;
		return S_OK;
	}
	if ( IsEqualIID(riid, __uuidof(IDownload)) )
	{
		return CreateDownloadObject(riid,ppvObj);
	}
	if(
		IsEqualIID(riid, __uuidof(ISoftUninstall)) ||
		IsEqualIID(riid, __uuidof(ISoftUninstall2))
		)
	{
		*ppvObj = new CSoftUninstall;
		return S_OK;
	}
	if(IsEqualIID(riid, __uuidof(ISoftInfoQuery)))
	{
		*ppvObj = new CSoftInfoQuery;
		return S_OK;
	}
	if(IsEqualIID(riid, __uuidof(ISoftInstall)))
	{
		*ppvObj = new CSoftInstall;
		return S_OK;
	}
	return E_NOINTERFACE;
}




#ifdef _DEBUG

//以下是测试代码

#include <winunit/WinUnit.h>
//#include <atlfile.h>
//BEGIN_TEST(LoadSoftDB)
//{
//	CDTManager* dt=new CDTManager;
//	dt->Init(NULL);
//	CAtlArray<CString>* arr=new CAtlArray<CString>;
//	arr->Add(L"http://www.vidown.cn/download.php");
//	void* tk=dt->NewTask(arr,L"",L"E:\\c.zip");
//	//dt->NewTask(arr,L"C:\\ksDownloads\\d.zip");
//	//dt->ResumeTask(tk);
//	//Sleep(15000);
//	//dt->PauseTask(tk);
//	//dt->StopTask(tk);
//	//dt->CancelTask(tk);
//	IDownload* download=(IDownload*)tk;
//	download->Wait();
//
//	//CAtlFile cf;
//	//cf.Create(L"C:\\ksDownloads\\softurl.txt",GENERIC_READ,FILE_SHARE_READ,OPEN_EXISTING);
//	//CStringA buff;
//	//ULONGLONG size;
//	//cf.GetSize(size);
//	//DWORD rd;
//	//cf.Read(buff.GetBuffer(size),size,rd);
//	//wchar_t* de;
//	//CString buff2=buff;
//	//wchar_t* tok=wcstok_s(buff2.GetBuffer(size),L"\n",&de);
//	//tok=wcstok_s(NULL,L"\n",&de);
//	//IDownload* download[5]={NULL};
//	//while (tok)
//	//{
//	//	CString url=tok;
//	//	CString id=url.Left(url.Find(_T("\t")));
//	//	url=url.Right(url.GetLength()-url.Find(_T("\t"))-1);
//	//	CString fff=L"D:\\ksdown\\"+id;
//	//	printf("%s\n",CW2A(id).m_psz);
//	//	if(PathFileExists(fff))
//	//	{
//	//		tok=wcstok_s(NULL,L"\n",&de);
//	//		continue;
//	//	}
//	//	//fff.Format(L"D:\ksdown\\%d",i++);
//	//	for(int i=0;i<5;i++)
//	//	{
//	//		if(i==4)
//	//		{
//	//			for (int j=0;j<i;j++)
//	//			{
//	//				download[j]->Wait();
//	//				delete download[j];
//	//				download[j]=NULL;
//	//			}
//	//		}
//	//		if(download[i]==NULL)
//	//		{
//	//			CreateIDownload(__uuidof(IDownload),(void**)&download[i]);
//	//			download[i]->SetDownloadInfo(tok,fff);
//	//			download[i]->Start();	
//	//		}
//	//	}
//	//	tok=wcstok_s(NULL,L"\n",&de);
//	//}
//
//}
//END_TEST

//BEGIN_TEST(LoadSoftDB)
//{
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("soft.xml")==0); 
//}
//END_TEST

//int TestInsCheck(CString id,CString name,DWORD dwMS,DWORD dwLS,void* param)
//{
//	printf("%s\n",CW2A(name).m_psz);
//	return (int)param;
//}

//BEGIN_TEST(LoadSoftDB)
//{
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("softmgr.dat")==0); 
//	int i=g_sm.GetSoftCount(L"");
//	printf("\n%d\n",i);
//	//g_sc.CheckOneInstalled(L"50000001",TestInsCheck,0);
//	//WIN_ASSERT_TRUE(g_sc.Combine("fix.dat")==0); 
//	//WIN_ASSERT_TRUE(g_sm.LoadSoftDB("softmgr.dat")==0); 
//	//WIN_ASSERT_TRUE(g_sm.Combine("softmgrfix.dat")==0); 
//}
//END_TEST




//BEGIN_TEST(GetEssentialSoft)
//{
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB(L"softmgr.dat")==0);
//	g_sm.LoadRank(L"ranknew.dat");
//	void* pos=g_sm.GetAllSoft(L"",L"ar");
//	//void* pos=g_sm.GetLast50Soft();
//	CAtlMap<CString,CString> item;
//	while(0==g_sm.GetNextSoft(pos,item))
//	{
//		CString a=item[L"softid"];
//		printf("%s\n",CW2A(a).m_psz);
//		a=item[L"softname"];
//		printf("%s\n",CW2A(a).m_psz);
//	}
//}
//END_TEST
////
//BEGIN_TEST(GetAllSoft)
//{
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("soft.xml")==0);
//	printf("%d\n",g_sm.GetSoftCount(L""));
//	printf("%d\n",g_sm.GetSoftCount(L"视频播放"));
//	void* pos=g_sm.GetAllSoft(L"");
//	CAtlMap<CString,CString> item;
//	while(0==g_sm.GetNextSoft(pos,item))
//	{
//		CString a=item[L"softname"];
//		//printf("%s\n",CW2A(a).m_psz);
//	}
//	g_sm.FinalizeGet(pos);
//}
//END_TEST

//BEGIN_TEST(SearchSoft)
//{
//	g_sm.FreeSoftDB();
//	(g_sm.LoadRank("rank.xml")==L"df");
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("soft.xml")==0);
//	void* pos=g_sm.SearchSoft(L"360安全卫士 7.0正式版",L"");
//	CAtlMap<CString,CString> item;
//	while(0==g_sm.GetNextSoft(pos,item))
//	{
//		CString a=item[L"filename"];
//		printf("%s\n",CW2A(a).m_psz);
//	}
//	g_sm.FinalizeGet(pos);
//}
//END_TEST

//BEGIN_TEST(LoadRank)
//{
//	(g_sm.LoadRank("rank.xml")==L"df");
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("soft.xml")==0);
//	void* pos=g_sm.GetAllSoft(L"",L"df");
//	CAtlMap<CString,CString> item;
//	while(0==g_sm.GetNextSoft(pos,item))
//	{
//		CString a=item[L"softname"];
//		printf("%s\n",CW2A(a).m_psz);
//	}
//	g_sm.FinalizeGet(pos);
//}
//END_TEST

//int TestUniInfo(CString key,CString name,CString disp_icon,CString loc,CString uni_cmd,CString parent,void* param)
//{
//	CString a=g_sm.GetUnistallInfo(name);
//	if(a!=L"")
//		printf("%s\n%s\n",CW2A(name).m_psz,CW2A(a).m_psz);
//	else
//		printf("#\n没找到:%s\n",CW2A(name).m_psz);
//	return 0;
//}
//
//
//BEGIN_TEST(GetUnistallInfo)
//{
//	CSoftChecker sc;
//	//WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0); 
//	g_sm.FreeSoftDB();
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("softmgrup.dat")==0);
//	CString a=g_sm.GetUnistallInfo(L"360安全卫士");
//	printf("%s\n",CW2A(a).m_psz);
//	a=g_sm.GetUnistallInfo(L"彩虹网络电视");
//	WIN_ASSERT_TRUE(sc.CheckAll2Unistall(TestUniInfo,&g_sm)==0); 
//}
//END_TEST
//
//BEGIN_TEST(GetCatalog)
//{
//	CSoftChecker sc;
//	//WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0); 
//	g_sm.FreeSoftDB();
//	WIN_ASSERT_TRUE(g_sm.LoadSoftDB("soft.xml")==0);
//	CAtlArray<CString> re;
//	g_sm.GetCatalog(GetCatlogUseArr,&re);
//	WIN_ASSERT_TRUE(re.GetCount()>0);
//}
//END_TEST

#define _SOFTCHECK_TEST

#ifdef _SOFTCHECK_TEST



//int TestInsCheck(CString id,CString name,DWORD dwMS,DWORD dwLS,void* param)
//{
//	printf("%s\n",CW2A(name).m_psz);
//	return (int)param;
//}
//
int TestUniCheck(CString key,CString name,CString disp_icon,CString loc,CString uni_cmd,CString parent,void* param)
{
	printf("%s\t%s\n",CW2A(key).m_psz,CW2A(name).m_psz);
	return (int)param;
}
//
//
//BEGIN_TEST(Load)
//{
//	WIN_ASSERT_TRUE(g_sc.Load(L"fuck.xml")==-1); 
//
//	WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0);   
//	
//	WIN_ASSERT_TRUE(g_sc.GetSoftCount()==857);
//
//	WIN_ASSERT_TRUE(g_sc.Load(L"newlib.xml")==0);
//
//	WIN_ASSERT_TRUE(g_sc.GetSoftCount()!=857);
//}
//END_TEST
//
//BEGIN_TEST(CheckAllInstalled)
//{
//	//WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0); 
//	WIN_ASSERT_TRUE(g_sc.CheckAllInstalled(TestInsCheck,NULL)==0); 
//	WIN_ASSERT_TRUE(g_sc.CheckAllInstalled(TestInsCheck,(void*)1)==0); 
//	WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0);
//	WIN_ASSERT_TRUE(g_sc.CheckAllInstalled(TestInsCheck,NULL)==0); 
//	WIN_ASSERT_TRUE(g_sc.CheckAllInstalled(TestInsCheck,(void*)1)==1); 
//}
//END_TEST
//
//BEGIN_TEST(CheckOneInstalled)
//{
//	//WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0); 
//	WIN_ASSERT_TRUE(g_sc.Load(L"softmgrup.dat")==0);
//	WIN_ASSERT_TRUE(g_sc.CheckOneInstalled(L"115",TestInsCheck,NULL)==0); 
//	WIN_ASSERT_TRUE(g_sc.CheckOneInstalled(L"145",TestInsCheck,(void*)1)==1); 
//}
//END_TEST
//
#include "file_util.h"
int UniCheckCallBackExTest(void* mp,void* param)
{
	CAtlMap<CString,CString>& m=*(CAtlMap<CString,CString>*)mp;
	printf("%s\n",CW2A(m[L"name"]).m_psz);
	printf("%s\n",CW2A(m[L"pname"]).m_psz);
	printf("%s\n",CW2A(m[L"loc"]).m_psz);
	

	//if(m[L"loc"].GetLength()>4)
	//{
	//	struct  
	//	{
	//		double size;
	//		bool operator()(CString dir,_wfinddata_t& info)
	//		{
	//			//CString f=dir+L"\\"+info.name;
	//			if(info.name[0]=='.')
	//				return false;
	//			size+=info.size;
	//			if(info.attrib| _A_SUBDIR)
	//				ForeachFile(dir+L"\\"+info.name,*this);
	//			//CAtlFile file;
	//			//file.Create(f,0,FILE_SHARE_DELETE,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS);
	//			//BY_HANDLE_FILE_INFORMATION hinfo={0};
	//			//GetFileInformationByHandle(file.m_h,&hinfo);
	//			//printf("%0.8x %0.8x (%0.8x):%s\n",hinfo.nFileIndexHigh,hinfo.nFileIndexLow,info.size,CW2A(f).m_psz);
	//			return false;
	//		}
	//	}func;

	//	//ForeachFile(argv[1],func);
	//	func.size=0;
	//	ForeachFile(m[L"loc"],func);
	//	printf("%.2f MB\n",func.size/1024/1024);
	//}


	printf("---------------------------------------------------\n");

	m.RemoveAll();
	return 0;
}

BEGIN_TEST(CheckAll2Unistall)
{
	g_sc.LoadUnInfo(L"SoftUninst.dat");

	g_sc.CheckAll2UninstallByType(g_sc.STARTMENU,UniCheckCallBackExTest,GetInfoUseMap,new CAtlMap<CString,CString>,NULL);

}
END_TEST
//BEGIN_TEST(CheckAll2Unistall)
//{
//	//WIN_ASSERT_TRUE(g_sc.Load(L"softmgrup.dat")==0); 
//	//g_sc.__get_lnk_path(L"C:\\Documents and Settings\\All Users\\「开始」菜单\\程序\\StarDict\\StarDict.lnk");
//	g_sc.LoadUnInfo(L"SoftUninst.dat");
//	//g_sc.CheckAll2Uninstall(UniCheckCallBackExTest,GetInfoUseMap,new CAtlMap<CString,CString>,NULL);
//	//g_sc.CheckOne2Uninstall(L"{03DDA387-EBB9-49CD-9899-A7E8A6E78946}",UniCheckCallBackExTest,GetInfoUseMap,new CAtlMap<CString,CString>,NULL);
//	g_sc.CheckAll2UninstallByType(g_sc.STARTMENU,UniCheckCallBackExTest,GetInfoUseMap,new CAtlMap<CString,CString>,NULL);
//	//g_sm.LoadSoftDB(L"softmgr_2010.5.8.2.dat");
//	//g_sm.Combine("softmgr_2010.5.8.2_2010.5.9.1_inc.dat");
//	//g_sc.LoadUnInfo(L"SoftUninst_old.dat");
//	//g_sc.Combine_UniInfo(L"SoftUninst_fix.dat");
//
//	//void* pos=g_sc.SearchUninstallItem(L"qq");
//	//CString re;
//	//do 
//	//{
//	//	re=g_sc.GetNextItem(pos);
//	//	printf("%s\n",CW2A(re).m_psz);
//	//} while (FALSE==re.IsEmpty());
//
//	//WIN_ASSERT_TRUE(g_sc.CheckAll2Uninstall(TestUniCheck,NULL)==0); 
//	/*WIN_ASSERT_TRUE(g_sc.CheckAll2Unistall(TestUniCheck,(void*)1)==1); */
//}
//END_TEST
//
//BEGIN_TEST(CheckOne2Unistall)
//{
//	//WIN_ASSERT_TRUE(g_sc.Load(L"softup.xml")==0); 360°²È«ÎÀÊ¿
//	//WIN_ASSERT_THROWS(g_sc.CheckOne2Unistall(L"",TestUniCheck,NULL)==0,wchar_t*); 
//	//WIN_ASSERT_THROWS(g_sc.CheckOne2Unistall(L"",TestUniCheck,(void*)1),wchar_t*); 
//	WIN_ASSERT_TRUE(g_sc.CheckOne2Unistall(L"360°²È«ÎÀÊ¿",TestUniCheck,NULL)==0);
//	WIN_ASSERT_TRUE(g_sc.CheckOne2Unistall(L"°²È«ÎÀÊ¿",TestUniCheck,NULL)==-1);
//}
//END_TEST

//BEGIN_TEST(Uninstall)
//{
//	//WIN_ASSERT_TRUE(g_sc.Uninstall(L"cmd.exe")==1); 
//	WIN_ASSERT_TRUE(g_sc.Uninstall(L"C:\\Program Files\\Thunder Network\\Xmp\\Uninstall.exe")==0); 
//}
//END_TEST

//int TestPowerSweepCallBack(CString type,CString path,void* param)
//{
//	printf("%s\n",CW2A(path).m_psz);
//	return (int)param;
//}
//
//BEGIN_TEST(Uninstall)
//{
//	//WIN_ASSERT_TRUE(g_sc.Uninstall(L"cmd.exe")==1); 
//	//g_sc.PowerSweep(L"Wireshark",L"C:\\Program Files\\Wireshark",TestPowerSweepCallBack,0);
//	g_sc.PowerSweep(L"Everything",L"C:\\Program Files\\Everything",TestPowerSweepCallBack,(void*)0);
//	//g_sc.PowerSweep(L"{9C19FFB1-25FC-43FC-AC78-919E5E2A6DD0}",L"C:\\Program Files\\TortoiseSVN",TestPowerSweepCallBack,0);
//}
//END_TEST

//C:\Program Files\Thunder Network\Xmp\Uninstall.exe
#endif // _SOFTCHECK_TEST

#endif
