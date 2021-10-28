#pragma once

#include <windows.h>

class IppDib
{
private:
	BOOL LoadBMP(const char* filename);
	BOOL SaveBMP(const char* filename);

	LONG	m_nWidth;
	LONG	m_nHeight;
	WORD	m_nBitCount;
	DWORD	m_nDibSize;
	BYTE*	m_pDib;

public:
	IppDib();
	IppDib(const IppDib& dib);
	~IppDib();

	BOOL CreateGrayBitmap(LONG nWidth, LONG nHeight);
	BOOL CreateRgbBitmap(LONG nWidht, LONG nHeight);
	void DestroyBitmap();

	BOOL Load(const char* filename);
	BOOL Save(const char* filename);

	void Draw(HDC hdc, int dx = 0, int dy = 0);
	void Draw(HDC hdc, int dx, int dy, int dh, DWORD dwRop = SRCCOPY);
	void Draw(HDC hdc, int dx, int dy, int dh, int sx, int sy, int sw, int sh, DWORD dwRop = SRCCOPY);

	BOOL CopyClipboard();
	BOOL PasteFromClipboard();

	IppDib& operator=(const IppDib& dib);

	LONG		GetWidth()			const { return m_nWidth; };
	LONG		GetHeight()			const { return m_nHeight; }
	WORD		GetBitCount()		const { return m_nBitCount; }
	DWORD		GetBitSize()		const { return m_nDibSize; }
	LPBITMAP	GetBitmapInfoAddr()	const { return (LPBITMAPINFO)m_pDib; }
	BYTE*		GetDIBBitsAddr()	const;
	int			GetPlaetteNums()	const;
	BOOL		IsValidd()			const { return (m_pDib != NULL); }
};
