#include"CTabSheet.h"
#include"pch.h"
IMPLEMENT_DYNAMIC(CTabSheet, CTabCtrl)

BEGIN_MESSAGE_MAP(CTabSheet,CTabCtrl)
ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnTcnSelchange)
ON_WM_SIZE()
END_MESSAGE_MAP()

CTabSheet::CTabSheet()
{
	current_page = -1;
	pagex = 0;
	pagey = 20;
}

CTabSheet::~CTabSheet()
{
}

void CTabSheet::OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	CRect rec;
	GetClientRect(&rec);
	int a=GetCurFocus();
	pages[current_page].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_HIDEWINDOW);
	pages[a].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
	current_page = a;
}

BOOL CTabSheet::AddPage(int pagenum, LPCTSTR pagename, UINT pageID,CDialog *pPage, BOOL whether_show_now)
{
	if (pPage == NULL) return NULL_PAGE;
	if (pagenum > pages.size()) return ADD_OUT;
	page p;
	p.pageItem = pPage;
	p.ID = pageID;
	p.title = pagename;
	int a = pages.size();
	if (pagenum == pages.size())
		pages.push_back(p);
	else
		pages.insert(pages.begin()+pagenum,p);


	CRect rec;
	GetClientRect(&rec);
	InsertItem(pagenum, pagename);
	BOOL b;
	b=pPage->Create(pageID, this);
	if (b == FALSE) return FALSE;
	if (current_page == -1)
	{
		b = pPage->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
		current_page = pagenum;
		if (whether_show_now == FALSE) return NO_CURRENT_PAGE;
		return b;
	}
	if (whether_show_now)
	{
		pages[current_page].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_HIDEWINDOW);
		b = pPage->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
		SetCurFocus(pagenum);
	}
	else
		b=pPage->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_HIDEWINDOW);
	return b;
}

BOOL CTabSheet::AddPageInEnd(LPCTSTR pagename, UINT pageID, CDialog* pPage, BOOL whether_show_now)
{
	//int pagenum = pages.size();
	BOOL b =AddPage(pages.size(), pagename, pageID, pPage, whether_show_now);
	return b;
}



int CTabSheet::GetCurrentPage()
{
	if (current_page == -1)
		return NO_CURRENT_PAGE;
	return current_page;
}


BOOL CTabSheet::GetCurrentPage(page& page_struct)
{
	if (current_page == -1)
		return NO_CURRENT_PAGE;
	page_struct = pages[current_page];
}

BOOL CTabSheet::GetCurrentPage(int& pagenum, page& page_struct)
{
	if (current_page == -1)
		return NO_CURRENT_PAGE;
	pagenum = current_page;
	page_struct = pages[current_page];
}

BOOL CTabSheet::DeletePage(CString name)
{
	for (int i = 0; i < pages.size(); i++)
	{
		if (pages[i].title == name)
		{
			DeletePage(i);
			return TRUE;
		}
	}
	return DELETE_NOT_FOUND;
}

BOOL CTabSheet::DeletePage(int pagenum)
{
	if (pagenum > pages.size() - 1)
		return DELETE_OUT;
	CRect rec;
	GetClientRect(&rec);
	pages[pagenum].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_HIDEWINDOW);
	DeleteItem(pagenum);
	pages.erase(pages.begin()+pagenum);
	if (pages.size() == 0)
	{
		current_page = -1;
		return TRUE;
	}
	if (current_page==pagenum)
	{
		if (current_page == 0)
			pages[pagenum].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
		else
		{
			current_page = pagenum - 1;
			pages[pagenum - 1].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
		}
	}
	else if (current_page>pagenum)
	{
		current_page--;
		pages[current_page].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
	}
	return TRUE;
}

BOOL CTabSheet::DeleteCurrentPage()
{
	if (current_page == -1)
		return NO_CURRENT_PAGE;
	DeletePage(current_page);
	return TRUE;
}

int CTabSheet::FindPage(CString pagename)
{
	for (int i = 0; i < pages.size(); i++)
		if (pages[i].title == pagename)
			return i;
	return -1;
}

BOOL CTabSheet::FindPage(CString pagename, page &p)
{
	for (int i = 0; i < pages.size(); i++)
		if (pages[i].title == pagename)
		{
			p = pages[i];
			return TRUE;
		}
	return FALSE;
}


void CTabSheet::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	if (current_page == -1)
		return;

	CRect rec;
	GetClientRect(&rec);
	pages[current_page].pageItem->SetWindowPos(NULL, pagex, pagey, rec.Width() - pagex, rec.Height() - pagey, SWP_SHOWWINDOW);
}
