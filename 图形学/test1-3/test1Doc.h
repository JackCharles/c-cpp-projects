// test1Doc.h : interface of the CTest1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST1DOC_H__A8C286E3_3B7B_4AC8_ACA3_61C536D02651__INCLUDED_)
#define AFX_TEST1DOC_H__A8C286E3_3B7B_4AC8_ACA3_61C536D02651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTest1Doc : public CDocument
{
protected: // create from serialization only
	CTest1Doc();
	DECLARE_DYNCREATE(CTest1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTest1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1DOC_H__A8C286E3_3B7B_4AC8_ACA3_61C536D02651__INCLUDED_)
