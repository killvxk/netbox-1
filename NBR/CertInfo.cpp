#include "StdAfx.h"
#include "CertInfo.h"
#include <openssl\rsa.h>

static const unsigned char pk[] = {0x30, 0x82, 0x02, 0x0A, 0x02, 0x82, 0x02, 0x01, 0x00, 0xE4, 0x95, 0xE5, 0xD3, 0xCE, 0x33,
0xF9, 0xD1, 0x49, 0x49, 0x2D, 0x5D, 0x32, 0xD9, 0x29, 0x53, 0xDD, 0xF8, 0x79, 0x9E, 0xD6,
0x8F, 0x91, 0xB5, 0x61, 0xCC, 0x13, 0xEA, 0x04, 0x96, 0x48, 0x42, 0xE2, 0x82, 0x0C, 0x94,
0x17, 0x89, 0xDB, 0x3E, 0x6C, 0x84, 0x2E, 0x69, 0x12, 0x3E, 0xF2, 0xAC, 0x1D, 0xBF, 0x27,
0x92, 0x57, 0xCA, 0xAE, 0xE1, 0xE2, 0xC9, 0xDB, 0x10, 0x2E, 0xE3, 0xA2, 0x75, 0x60, 0x78,
0x85, 0x1C, 0xED, 0xDC, 0x81, 0xD7, 0x9F, 0x91, 0x6E, 0x67, 0x6A, 0x0E, 0x5D, 0x08, 0xFC,
0x5A, 0x1D, 0x1A, 0x44, 0x00, 0x28, 0x5E, 0x1A, 0x9C, 0x30, 0x06, 0x4E, 0xAD, 0x35, 0x46,
0x27, 0x11, 0x28, 0x84, 0xD8, 0xD6, 0x05, 0x09, 0x89, 0x76, 0x20, 0x6A, 0x6D, 0xBE, 0x82,
0x23, 0x02, 0x9C, 0x44, 0x61, 0x13, 0x77, 0x37, 0x22, 0x60, 0xD4, 0xCE, 0x91, 0xF0, 0xA3,
0x92, 0x4A, 0x63, 0xD7, 0x32, 0xDF, 0x83, 0x47, 0x31, 0xAB, 0x6F, 0x0E, 0x90, 0x3D, 0xFD,
0xCE, 0x16, 0x39, 0x5E, 0x18, 0xD6, 0xF0, 0xAA, 0x0E, 0x48, 0xA6, 0x2F, 0x68, 0x7B, 0xC6,
0x9E, 0x0A, 0x2D, 0x55, 0xA8, 0xB4, 0x82, 0xEF, 0x3D, 0xE0, 0x48, 0x91, 0x5B, 0x2B, 0x66,
0xF3, 0xFC, 0x00, 0xBA, 0xB1, 0xA7, 0x2C, 0x59, 0xD6, 0x26, 0x0D, 0x4B, 0x59, 0xE9, 0xE7,
0x5B, 0x98, 0x81, 0xDE, 0x87, 0x33, 0x8B, 0x5B, 0x1B, 0x0A, 0x2A, 0x23, 0x80, 0x9A, 0x56,
0xDC, 0xD7, 0x6F, 0x05, 0x68, 0xD1, 0xD8, 0xF5, 0x84, 0xED, 0xA3, 0x92, 0x38, 0x19, 0x68,
0xC7, 0xD0, 0x8B, 0xA5, 0xEF, 0x10, 0x48, 0x8B, 0x1B, 0x6F, 0x53, 0xCB, 0xDB, 0xA2, 0x82,
0xEC, 0xF5, 0x6A, 0xDB, 0xDA, 0x2E, 0xA9, 0xFE, 0xB7, 0x84, 0xF8, 0x9A, 0xC2, 0xDB, 0xA6,
0xD2, 0xD6, 0xFF, 0x41, 0x6C, 0x2E, 0x18, 0x4E, 0x98, 0xD9, 0x68, 0xFA, 0xD2, 0xDC, 0x03,
0xF3, 0x9D, 0x56, 0xD2, 0x98, 0xE4, 0x97, 0x27, 0x0E, 0x2F, 0x2D, 0xB9, 0xA6, 0xA3, 0x19,
0xCC, 0xB7, 0x76, 0xA1, 0x66, 0xC5, 0x48, 0x62, 0xC6, 0x63, 0x99, 0xB3, 0xB7, 0x3E, 0xC9,
0x80, 0x33, 0xB5, 0x73, 0x8E, 0x3F, 0x96, 0x09, 0xAA, 0x69, 0x7B, 0x70, 0x7E, 0xE1, 0xC2,
0xCB, 0xFB, 0xF5, 0x4E, 0xEB, 0x39, 0x6F, 0xC6, 0xED, 0x6D, 0xB8, 0xE9, 0xAA, 0xBD, 0xFE,
0xAB, 0xA4, 0xE9, 0xC9, 0xFC, 0x86, 0x9E, 0x70, 0xBF, 0xB1, 0xAB, 0x6B, 0x61, 0x18, 0x72,
0x58, 0x2F, 0x05, 0x6D, 0x11, 0xEF, 0x67, 0x26, 0x2C, 0x35, 0x4A, 0x3A, 0x0D, 0x77, 0xE0,
0x1B, 0x20, 0xE9, 0x60, 0x09, 0x1B, 0xC5, 0x09, 0xC6, 0xD0, 0x65, 0xE2, 0x62, 0xFE, 0x77,
0xD0, 0x45, 0x2D, 0xB7, 0x5A, 0x5E, 0xB4, 0xC3, 0x30, 0x75, 0x66, 0xA6, 0x07, 0x6F, 0x95,
0xA2, 0xE3, 0x64, 0x8E, 0x24, 0xFA, 0x5C, 0x93, 0x76, 0x1C, 0xA8, 0x47, 0x10, 0xE5, 0x82,
0x8C, 0xA6, 0xF5, 0xC9, 0xEC, 0xEF, 0x1D, 0x11, 0x23, 0xA1, 0x98, 0xB4, 0x91, 0x2D, 0x2A,
0xFF, 0x19, 0x84, 0x33, 0xDE, 0xDC, 0x79, 0x6F, 0x3E, 0x15, 0x19, 0xE4, 0xAD, 0xAA, 0xF8,
0x60, 0x5C, 0xAA, 0x5B, 0xE4, 0x20, 0x03, 0x90, 0x0B, 0xBC, 0x79, 0x22, 0xA3, 0xE8, 0xB1,
0xCB, 0x58, 0xB1, 0xF5, 0x54, 0xC5, 0x24, 0x91, 0x9A, 0xF9, 0x5F, 0x62, 0xCD, 0x55, 0x3C,
0xDE, 0xC4, 0x0E, 0xAE, 0x6A, 0xB2, 0x62, 0x33, 0x53, 0x53, 0xB2, 0xB3, 0xF2, 0x84, 0xAC,
0x2B, 0x66, 0x0A, 0xF3, 0x71, 0x32, 0x91, 0x7C, 0x94, 0xD6, 0x71, 0x12, 0x31, 0xFA, 0x20,
0x52, 0xD2, 0x62, 0xBC, 0xC7, 0xB7, 0xEB, 0xB9, 0xD7, 0xD8, 0x99, 0x7E, 0x8E, 0xD2, 0x2B,
0xD4, 0xEE, 0x3A, 0x21, 0xF5, 0xF5, 0x70, 0x16, 0x23, 0x16, 0xF9, 0x02, 0x03, 0x01, 0x00,
0x01};

CCertInfo::CCertInfo(void)
{
	Clear();
}

CCertInfo::~CCertInfo(void)
{
}

void CCertInfo::Clear(void)
{
	ZeroMemory(m_aHash, sizeof(m_aHash));
	m_nDevID = 0;
	m_strStart.Empty();
	m_strEnd.Empty();
	m_bUpdate = TRUE;
	m_bValid = FALSE;
	m_dateTimeout = (DATE)0;
}

void CCertInfo::CheckDate(DATE d)
{
	m_bValid = m_dateEnd > d;
}

BOOL CCertInfo::SetLic(void* pBuffer)
{
	const unsigned char *ppk = pk;

	Clear();

	RSA *pRSA = NULL;

	pRSA = d2i_RSAPublicKey(&pRSA, &ppk, sizeof(pk));
	if(pRSA)
	{
		BYTE Lic[513];
		char *p1, *p2;
		int nSize = RSA_public_decrypt(512, (const BYTE*)pBuffer, Lic, pRSA, 1);

		if(nSize > 0)
		{
			CBDate d, d1;
			SYSTEMTIME st;
			Lic[nSize] = 0;
			CopyMemory(m_aHash, Lic, sizeof(m_aHash));
			p1 = (char*)Lic + sizeof(m_aHash);

			if(*p1 != '|')
			{
				Clear();
				RSA_free(pRSA);

				return FALSE;
			}

			d1.GetTime();

			p1 ++;
			p2 = p1;
			while(*p2 && *p2 != '|')p2 ++;
			*p2 = 0;
			m_nDevID = atoi(p1);

			p2 ++;
			p1 = p2;
			while(*p2 && *p2 != '|')p2 ++;
			m_strStart.SetString(p1, (int)(p2 - p1));

			ZeroMemory(&st, sizeof(st));
			st.wYear = atoi(m_strStart);
			st.wMonth = atoi((LPCTSTR)m_strStart + 5);
			st.wDay = atoi((LPCTSTR)m_strStart + 8);
			d = st;

			m_bUpdate = d1.Diff(CBDate::modeDay, d) > 30;

			p2 ++;
			p1 = p2;
			while(*p2 && *p2 != '|')p2 ++;
			m_strEnd.SetString(p1, (int)(p2 - p1));

			ZeroMemory(&st, sizeof(st));
			st.wYear = atoi(m_strEnd);
			st.wMonth = atoi((LPCTSTR)m_strEnd + 5);
			st.wDay = atoi((LPCTSTR)m_strEnd + 8);
			m_dateEnd = st;

			if(*p2)
			{
				p2 ++;

				ZeroMemory(&st, sizeof(st));
				st.wYear = atoi(p2);
				st.wMonth = atoi(p2 + 5);
				st.wDay = atoi(p2 + 8);

				m_dateTimeout = st;
			}
		}else
		{
			Clear();
			RSA_free(pRSA);
			return FALSE;
		}

		RSA_free(pRSA);
	}

	m_bValid = TRUE;

	return TRUE;
}
