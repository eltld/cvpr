
// ImageToolsDoc.h : CImageToolsDoc Ŭ������ �������̽�
//


#pragma once
#include "Dib.h"


class CImageToolsDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageToolsDoc();
	DECLARE_DYNCREATE(CImageToolsDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageToolsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// Image object
	CDib m_Dib;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnImaveInverse();
	afx_msg void OnImageBrightness();
	afx_msg void OnImageContrast();
	afx_msg void OnViewHistogram();
	afx_msg void OnHistogramEqualization();
	afx_msg void OnImageArithmetic();
	afx_msg void OnBitplaneSlicing();
	afx_msg void OnAddBitplane();
	afx_msg void OnFilterMean();
	afx_msg void OnFilterWeightedMean();
	afx_msg void OnFilterGaussian();
	afx_msg void OnImageTranslation();
	afx_msg void OnImageResize();
	afx_msg void OnImageRotate();
	afx_msg void OnChapter9Homework();
	afx_msg void OnImaheMirror();
	afx_msg void OnImageFlip();
	afx_msg void OnEdgeSobel();
	afx_msg void OnEdgePrewitter();
	afx_msg void OnEdgeRoberts();
	afx_msg void OnHarrisCorner();
	afx_msg void OnImageInverse();
	afx_msg void OnUpdateColorGrayscale(CCmdUI *pCmdUI);
	afx_msg void OnColorGrayscale();
	afx_msg void OnColorEdge();
	afx_msg void OnUpdateColorEdge(CCmdUI *pCmdUI);
	afx_msg void OnColorEqualize();
	afx_msg void OnUpdateColorEqualize(CCmdUI *pCmdUI);
	afx_msg void OnSegmentBinarization();
	afx_msg void OnBinarizationIterative();
	afx_msg void OnSegmentLabeling();
	afx_msg void OnContourTracing();
};
