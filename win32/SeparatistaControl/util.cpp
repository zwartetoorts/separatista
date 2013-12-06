/***************************************************************************
*   Copyright (C) 2013 by Okkel Klaver   *
*   info@vanhetland.nl   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include "util.h"
#include <comutil.h>

HRESULT VariantTypeFromCurrency(const char *pCurrency, VARIANT *pvCurrency)
{
	if (!pCurrency)
		return E_UNEXPECTED;

	*pvCurrency = _variant_t(pCurrency);
	return S_OK;
}

HRESULT DateTypeFromStdTime(time_t t, DATE *pDate)
{
	SYSTEMTIME stime;
	tm *pti;

	// Convert time_t to tm
	pti = localtime(&t);

	// Set SYSTEMTIME
	stime.wYear = pti->tm_year + 1900;
	stime.wMonth = pti->tm_mon + 1;
	stime.wDay = pti->tm_mday;
	stime.wHour = pti->tm_hour;
	stime.wMinute = pti->tm_min;
	stime.wSecond = pti->tm_sec;
	if (SystemTimeToVariantTime(&stime, pDate))
		return S_OK;

	return E_UNEXPECTED;
}