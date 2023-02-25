#pragma once
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <vector>

#define ADD_OUT 2			//添加的索引溢出
#define NO_CURRENT_PAGE 3	//当前未展示页面(若在AddPage()中，则强制展示插入的页面)
#define DELETE_OUT 4
#define DELETE_NOT_FOUND 5
#define NULL_PAGE 6

struct page {
	CDialog* pageItem;
	UINT ID;
	CString title;
};
class CTabSheet :public CTabCtrl
{
	DECLARE_DYNAMIC(CTabSheet)
	DECLARE_MESSAGE_MAP()
protected:
	//当前页面的索引
	int current_page;
	//存储所有的页面
	std::vector<page> pages;
	//页面切换
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//页面显示时的左上角横坐标（相对与tab控件）
	int pagex;
	//页面显示时的左上角纵坐标（相对与tab控件）
	int pagey;
public:
	CTabSheet();
	virtual ~CTabSheet();
	//根据索引添加页面
	BOOL AddPage(int pagenum, LPCTSTR pagename ,UINT pageID, CDialog* pPage, BOOL whether_show_now);
	//在最后添加页面
	BOOL AddPageInEnd(LPCTSTR pagename, UINT pageID, CDialog* pPage, BOOL whether_show_now);
	//返回当前页面的索引
	int GetCurrentPage();
	//返回当前页面的page结构体
	BOOL GetCurrentPage(page &page_struct);
	//返回当前页面的索引和结构体
	BOOL GetCurrentPage(int& pagenum, page& page_struct);
	//根据页面名称删除页面
	BOOL DeletePage(CString name);
	//根据索引删除页面
	BOOL DeletePage(int pagenum);
	//删除当前页面
	BOOL DeleteCurrentPage();
	//通过名称获取页面索引
	int FindPage(CString pagename);
	//通过名称获取页面page结构体
	BOOL FindPage(CString pagename,page &p);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};