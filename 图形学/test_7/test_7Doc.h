// test_7Doc.h : interface of the CTest_7Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_7DOC_H__0D1527EC_6719_4645_9BA8_3DB6D49DE209__INCLUDED_)
#define AFX_TEST_7DOC_H__0D1527EC_6719_4645_9BA8_3DB6D49DE209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTest_7Doc : public CDocument
{
protected: // create from serialization only
	CTest_7Doc();
	DECLARE_DYNCREATE(CTest_7Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_7Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTest_7Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest_7Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_7DOC_H__0D1527EC_6719_4645_9BA8_3DB6D49DE209__INCLUDED_)
