#pragma once
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <vector>

#define ADD_OUT 2			//��ӵ��������
#define NO_CURRENT_PAGE 3	//��ǰδչʾҳ��(����AddPage()�У���ǿ��չʾ�����ҳ��)
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
	//��ǰҳ�������
	int current_page;
	//�洢���е�ҳ��
	std::vector<page> pages;
	//ҳ���л�
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//ҳ����ʾʱ�����ϽǺ����꣨�����tab�ؼ���
	int pagex;
	//ҳ����ʾʱ�����Ͻ������꣨�����tab�ؼ���
	int pagey;
public:
	CTabSheet();
	virtual ~CTabSheet();
	//�����������ҳ��
	BOOL AddPage(int pagenum, LPCTSTR pagename ,UINT pageID, CDialog* pPage, BOOL whether_show_now);
	//��������ҳ��
	BOOL AddPageInEnd(LPCTSTR pagename, UINT pageID, CDialog* pPage, BOOL whether_show_now);
	//���ص�ǰҳ�������
	int GetCurrentPage();
	//���ص�ǰҳ���page�ṹ��
	BOOL GetCurrentPage(page &page_struct);
	//���ص�ǰҳ��������ͽṹ��
	BOOL GetCurrentPage(int& pagenum, page& page_struct);
	//����ҳ������ɾ��ҳ��
	BOOL DeletePage(CString name);
	//��������ɾ��ҳ��
	BOOL DeletePage(int pagenum);
	//ɾ����ǰҳ��
	BOOL DeleteCurrentPage();
	//ͨ�����ƻ�ȡҳ������
	int FindPage(CString pagename);
	//ͨ�����ƻ�ȡҳ��page�ṹ��
	BOOL FindPage(CString pagename,page &p);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};