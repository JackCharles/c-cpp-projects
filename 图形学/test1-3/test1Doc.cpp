// test1Doc.cpp : implementation of the CTest1Doc class
//

#include "stdafx.h"
#include "test1.h"

#include "test1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc

IMPLEMENT_DYNCREATE(CTest1Doc, CDocument)

BEGIN_MESSAGE_MAP(CTest1Doc, CDocument)
	//{{AFX_MSG_MAP(CTest1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc construction/destruction

CTest1Doc::CTest1Doc()
{
	// TODO: add one-time construction code here

}

CTest1Doc::~CTest1Doc()
{
}

BOOL CTest1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTest1Doc serialization

void CTest1Doc::Serialize(CArchive& ar)
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
// CTest1Doc diagnostics

#ifdef _DEBUG
void CTest1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTest1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc commands
