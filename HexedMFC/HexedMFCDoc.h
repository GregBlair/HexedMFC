
// HexedMFCDoc.h : interface of the CHexedMFCDoc class
//


#pragma once
#include "PieceList.h"


class CHexedMFCDoc : public CDocument
{
protected: // create from serialization only
	CHexedMFCDoc() noexcept;
	DECLARE_DYNCREATE(CHexedMFCDoc)

// Attributes
public:

	PieceList m_pieceList;

// Operations
public:

	bool SetBlockCount(unsigned int blockCount);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CHexedMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
