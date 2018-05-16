// test_7Doc.cpp : implementation of the CTest_7Doc class
//

#include "stdafx.h"
#include "test_7.h"

#include "test_7Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest_7Doc

IMPLEMENT_DYNCREATE(CTest_7Doc, CDocument)

BEGIN_MESSAGE_MAP(CTest_7Doc, CDocument)
	//{{AFX_MSG_MAP(CTest_7Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_7Doc construction/destruction

CTest_7Doc::CTest_7Doc()
{
	// TODO: add one-time construction code here

}

CTest_7Doc::~CTest_7Doc()
{
}

BOOL CTest_7Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTest_7Doc serialization

void CTest_7Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTest_7Doc diagnostics

#ifdef _DEBUG
void CTest_7Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTest_7Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest_7Doc commands
