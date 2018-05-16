// test_6Doc.cpp : implementation of the CTest_6Doc class
//

#include "stdafx.h"
#include "test_6.h"

#include "test_6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest_6Doc

IMPLEMENT_DYNCREATE(CTest_6Doc, CDocument)

BEGIN_MESSAGE_MAP(CTest_6Doc, CDocument)
	//{{AFX_MSG_MAP(CTest_6Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest_6Doc construction/destruction

CTest_6Doc::CTest_6Doc()
{
	// TODO: add one-time construction code here

}

CTest_6Doc::~CTest_6Doc()
{
}

BOOL CTest_6Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTest_6Doc serialization

void CTest_6Doc::Serialize(CArchive& ar)
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
// CTest_6Doc diagnostics

#ifdef _DEBUG
void CTest_6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTest_6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest_6Doc commands
