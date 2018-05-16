// test_6Doc.h : interface of the CTest_6Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_6DOC_H__1F3AD547_DE3E_49B8_8039_0FD97EBA912E__INCLUDED_)
#define AFX_TEST_6DOC_H__1F3AD547_DE3E_49B8_8039_0FD97EBA912E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTest_6Doc : public CDocument
{
protected: // create from serialization only
	CTest_6Doc();
	DECLARE_DYNCREATE(CTest_6Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_6Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTest_6Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest_6Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_6DOC_H__1F3AD547_DE3E_49B8_8039_0FD97EBA912E__INCLUDED_)
