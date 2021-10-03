# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <cstdlib>
# include <cstdio>
# include <cassert>
// assert GetACP 1252
constexpr wchar_t CP1252[256]
{
L'\0',     1,     2,     3,     4,     5,     6, L'\a', // ASCII
L'\b', L'\t', L'\n', L'\v', L'\f', L'\r',    14,    15, // ASCII
   16,    17,    18,    19,    20,    21,    22,    23, // ASCII
   24,    25,    26,    27,    28,    29,    30,    31, // ASCII
 L' ',  L'!',  L'"',  L'#',  L'$',  L'%',  L'&', L'\'', // ASCII
 L'(',  L')',  L'*',  L'+',  L',',  L'-',  L'.',  L'/', // ASCII
 L'0',  L'1',  L'2',  L'3',  L'4',  L'5',  L'6',  L'7', // ASCII
 L'8',  L'9',  L':',  L';',  L'<',  L'=',  L'>',  L'?', // ASCII
 L'@',  L'A',  L'B',  L'C',  L'D',  L'E',  L'F',  L'G', // ASCII
 L'H',  L'I',  L'J',  L'K',  L'L',  L'M',  L'N',  L'O', // ASCII
 L'P',  L'Q',  L'R',  L'S',  L'T',  L'U',  L'V',  L'W', // ASCII
 L'X',  L'Y',  L'Z',  L'[', L'\\',  L']',  L'^',  L'_', // ASCII
 L'`',  L'a',  L'b',  L'c',  L'd',  L'e',  L'f',  L'g', // ASCII
 L'h',  L'i',  L'j',  L'k',  L'l',  L'm',  L'n',  L'o', // ASCII
 L'p',  L'q',  L'r',  L's',  L't',  L'u',  L'v',  L'w', // ASCII
 L'x',  L'y',  L'z',  L'{',  L'|',  L'}',  L'~',   127, // ASCII
 L'€',   129,  L'‚',  L'ƒ',  L'„',  L'…',  L'†',  L'‡', // Windows-1252
 L'ˆ',  L'‰',  L'Š',  L'‹',  L'Œ',   141,  L'Ž',   143, // Windows-1252
  144,  L'‘',  L'’',  L'“',  L'”',  L'•',  L'–',  L'—', // Windows-1252
 L'˜',  L'™',  L'š',  L'›',  L'œ',   157,  L'ž',  L'Ÿ', // Windows-1252
  160,  L'¡',  L'¢',  L'£',  L'¤',  L'¥',  L'¦',  L'§', // ISO-8859-1
 L'¨',  L'©',  L'ª',  L'«',  L'¬',   173,  L'®',  L'¯', // ISO-8859-1
 L'°',  L'±',  L'²',  L'³',  L'´',  L'µ',  L'¶',  L'·', // ISO-8859-1
 L'¸',  L'¹',  L'º',  L'»',  L'¼',  L'½',  L'¾',  L'¿', // ISO-8859-1
 L'À',  L'Á',  L'Â',  L'Ã',  L'Ä',  L'Å',  L'Æ',  L'Ç', // ISO-8859-1
 L'È',  L'É',  L'Ê',  L'Ë',  L'Ì',  L'Í',  L'Î',  L'Ï', // ISO-8859-1
 L'Ð',  L'Ñ',  L'Ò',  L'Ó',  L'Ô',  L'Õ',  L'Ö',  L'×', // ISO-8859-1
 L'Ø',  L'Ù',  L'Ú',  L'Û',  L'Ü',  L'Ý',  L'Þ',  L'ß', // ISO-8859-1
 L'à',  L'á',  L'â',  L'ã',  L'ä',  L'å',  L'æ',  L'ç', // ISO-8859-1
 L'è',  L'é',  L'ê',  L'ë',  L'ì',  L'í',  L'î',  L'ï', // ISO-8859-1
 L'ð',  L'ñ',  L'ò',  L'ó',  L'ô',  L'õ',  L'ö',  L'÷', // ISO-8859-1
 L'ø',  L'ù',  L'ú',  L'û',  L'ü',  L'ý',  L'þ',  L'ÿ', // ISO-8859-1
};
constexpr LPCSTR szClassName = "1252";
LPVOID pvBits;
struct bmiHeader : BITMAPINFOHEADER {
	RGBQUAD bmiColors[2] {
		0x00, 0x00, 0x00, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF,
	};
	bmiHeader(void): BITMAPINFOHEADER {
		sizeof(BITMAPINFOHEADER),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1,
		1,
		BI_RGB,
	# pragma warning(suppress: 26450)
		CW_USEDEFAULT * CW_USEDEFAULT * 3,
		2835,
		2835,
		0,
		0
	} { }
	BITMAPINFO *operator &(void) {
		return reinterpret_cast<BITMAPINFO *>(this);
	}
} DIB ; // debaisu independento bittomappu
int x, y;
int w, h;
HDC debaisu = NULL;
////////////////////////////
BITMAPINFOHEADER *INFO;
BYTE *bmp;
////////////////////////////
CHAR BUFFER[512] {0};
BYTE LENGTH[256] {0};
USHORT OFFSET[256] {0};
////////////////////////////
DWORD saizu { }; // サイズ
LPSTR *fairu { }; // ファイル
POINT kāsoru { }; // カーソル
LRESULT CALLBACK fnWndProc(HWND uindō, UINT messēji, WPARAM wādo, LPARAM rongu) { // uindō puroshījā
	switch(messēji) {
	case WM_CREATE:
		debaisu = GetDC(uindō);
		DIB.biWidth = w / 2;
		DIB.biHeight = h / 2;
		DIB.biSizeImage = (w / 2 + 31) / 32 * 4 * h / 2;
		CreateDIBSection(debaisu, &DIB, DIB_RGB_COLORS, &pvBits, NULL, 0);
		{
			RAWINPUTDEVICE rōru·inputto·debaisu[2] {
				{1, 2, RIDEV_NOLEGACY&0, uindō}, // RAWMOUSE / RIM_TYPEMOUSE
				{1, 6, RIDEV_NOLEGACY&0, uindō} // RAWKEYBOARD / RIM_TYPEKEYBOARD
			};
			RegisterRawInputDevices(rōru·inputto·debaisu, 2, sizeof(RAWINPUTDEVICE));
		}
		return 0L;
	case WM_INPUT:
		// switch wādo case RIM_INPUTSINK return
		{
			UINT cbSize { };
			RAWINPUTHEADER RIH;
			HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(rongu);
			GetRawInputData(hRawInput, RID_HEADER, &RIH, &cbSize, sizeof(RAWINPUTHEADER));
			if(RIH.dwType == RIM_TYPEMOUSE)
			{
				RAWINPUT RAR;
				GetRawInputData(hRawInput, RID_INPUT, NULL, &cbSize, sizeof(RAWINPUTHEADER));
				LPVOID pData = malloc(cbSize);
				GetRawInputData(hRawInput, RID_INPUT, pData, &cbSize, sizeof(RAWINPUTHEADER));
				free(pData);
			}
			if(RIH.dwType == RIM_TYPEKEYBOARD)
			{
			}
		}
		return 0L;
	case WM_PAINT:
		//memset(static_cast<DWORD *>(pvBits) + (w / 2 + 31) / 32 * (h / 2 - 1), 255, (w / 2 + 31) / 32 * 4);
		for(int n=0; n<saizu; ++n) {
			LPSTR sz = fairu[saizu - 1 - n];
			for(int i=0; i<INFO->biHeight; ++i) {
				int x = 0;
				for(int j=0; sz[j]; ++j) {
					
					union {
						BYTE epi8[2];
						USHORT si16;
					};
					epi8[0] = ~bmp[OFFSET[sz[j]] / 8 + 0 + (INFO->biWidth + 31) / 32 * 4 * i];
					epi8[1] = ~bmp[OFFSET[sz[j]] / 8 + 1 + (INFO->biWidth + 31) / 32 * 4 * i];
					si16 >> OFFSET[sz[j]] % 8;
					si16 &= 0xFFFF >> 16 - LENGTH[sz[j]];
					//printf(" 0x%hx", si16);

					static_cast<BYTE *>(pvBits)[j + (DIB.biWidth + 31) / 32 * 4 * (i + INFO->biHeight * n)] = epi8[0];

					//LENGTH[sz[j]];
					//x += LENGTH[sz[j]] + 1;

					//static_cast<BYTE *>(pvBits)[j + (DIB.biWidth + 31 / 32) * 4 * i] = ~bmp[OFFSET[sz[j]] / 8 + (INFO->biWidth + 31) / 32 * 4 * i];
				}
				printf("\n");
			}
		}
		StretchDIBits(debaisu, 0, 0, w, h, 0, 0, DIB.biWidth, DIB.biHeight, pvBits, &DIB, DIB_RGB_COLORS, SRCCOPY);
		ValidateRect(uindō, NULL);
		return 0L;
	case WM_DESTROY:
		//ReleaseDC(uindō, debaisu);
		PostQuitMessage(0);
		return 0L;
	default:
		return DefWindowProc(uindō, messēji, wādo, rongu);
	}
}

# include <immintrin.h>
auto mm_sllv_epi16(__m128i xmm_0, __m128i xmm_1) {
    return _mm_packus_epi32(
        _mm_srli_epi32(_mm_slli_epi32(
        _mm_sllv_epi32(_mm_unpacklo_epi16(xmm_0, _mm_setzero_si128( )),
                       _mm_unpacklo_epi16(xmm_1, _mm_setzero_si128( ))), 16), 16),
        _mm_srli_epi32(_mm_slli_epi32(
        _mm_sllv_epi32(_mm_unpackhi_epi16(xmm_0, _mm_setzero_si128( )),
                       _mm_unpackhi_epi16(xmm_1, _mm_setzero_si128( ))), 16), 16)
    );
}
auto mm_srlv_epi16(__m128i xmm_0, __m128i xmm_1) {
    return _mm_packus_epi32(
        _mm_srlv_epi32(_mm_unpacklo_epi16(xmm_0, _mm_setzero_si128( )),
                       _mm_unpacklo_epi16(xmm_1, _mm_setzero_si128( ))),
        _mm_srlv_epi32(_mm_unpackhi_epi16(xmm_0, _mm_setzero_si128( )),
                       _mm_unpackhi_epi16(xmm_1, _mm_setzero_si128( )))
    );
}
# include <commdlg.h>
CHAR nēmu[MAX_PATH]; // ネーム
int main(int argc, const char *argv[ ]) {
	[ ](void) -> void {
		OPENFILENAME unnamedParam1 {
			sizeof(OPENFILENAME),
			NULL, // hwndOwner
			NULL, // hInstance
			"Text Documents (*.txt)\0*.TXT\0All Files (*.*)\0*.*\0",
			NULL, // lpstrCustomFilter
			0, // nMaxCustFilter
			1, // nFilterIndex
			nēmu, // lpstrFile
			sizeof(nēmu), // nMaxFile
			NULL, // lpstrFileTitle
			0, // nMaxFileTitle
			NULL, // lpstrInitialDir
			NULL, // lpstrTitle
			OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST
		};
		BOOL OpenFileName = GetOpenFileName(&unnamedParam1);
		assert(OpenFileName);
	}( );
	[ ](void) -> void {
		LPSTR baffā;
		HANDLE hFile = CreateFile(nēmu, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		assert(hFile != INVALID_HANDLE_VALUE);
		DWORD nFile = GetFileSize(hFile, NULL);
		baffā = static_cast<LPSTR>(malloc(nFile + 1));
		baffā[nFile] = '\n';
	# pragma warning(suppress: 6031)
		ReadFile(hFile, baffā, nFile, &nFile, NULL);
		CloseHandle(hFile);
		for(int n=0; n<=nFile; ++n) if(baffā[n] == '\n') ++ saizu;
		fairu = static_cast<LPSTR *>(malloc(sizeof(LPSTR) * saizu));
		LPSTR p = baffā;
		LPSTR q = baffā;
		for(int n=0; n<saizu; ++n) {
			while(*q && *q != '\n') ++ q;
	//	# pragma warning(suppress: 6011)
	//	# pragma warning(suppress: 6386)
	//	# pragma warning(suppress: 6387)
			fairu[n] = static_cast<LPSTR>(memcpy(malloc(q - p + 1), p, q - p));
			fairu[n][q - p] = '\0';
			p = ++ q;
		}
		free(baffā);
	}( );
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
	LCIDToLocaleName(MAKELCID(LOWORD(GetKeyboardLayout(NULL)), SORT_DEFAULT), localeName, LOCALE_NAME_MAX_LENGTH, 0);
	wprintf(L"%ls\n", localeName);

	WCHAR lang[MAX_PATH];
	GetLocaleInfoEx(localeName, LOCALE_SISO639LANGNAME2, lang, MAX_PATH);
	wprintf(L"%ls\n", lang);


	CHAR szKLID[MAX_PATH] {};
	GetKeyboardLayoutName(szKLID);
	printf("%s", szKLID);*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		WNDCLASS wc {
			CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
			fnWndProc,
			0,
			0,
			NULL,
			NULL,
			LoadCursor(NULL, IDC_ARROW),
			NULL,
			NULL,
			szClassName
		};
		RegisterClass(&wc);
	}
	EnumDisplayMonitors(NULL, NULL, [ ](HMONITOR, HDC, LPRECT lprc, LPARAM) -> BOOL {
		x = lprc->left;
		y = lprc->top;
		w = lprc->right - lprc->left;
		h = lprc->bottom - lprc->top;
		return TRUE;
	}, NULL);

	BITMAPFILEHEADER *FILE = static_cast<BITMAPFILEHEADER *>([ ](void) -> LPVOID {
		HMODULE hModule = GetModuleHandle(NULL);
		HRSRC hResInfo = FindResource(hModule, MAKEINTRESOURCE(1252), RT_RCDATA);
		assert(hResInfo != NULL);
		HGLOBAL hResData = LoadResource(hModule, hResInfo);
		assert(hResData != NULL);
		return LockResource(hResData);
		return NULL;
	}( ));
	
	INFO = reinterpret_cast<BITMAPINFOHEADER *>(FILE + 1);
	bmp = reinterpret_cast<BYTE *>(FILE) + FILE->bfOffBits;
	/*
	{
		int k=0;
		int n=0;
		for(int j=0; j<INFO->biWidth; ++j)
		{
			bool black = true;
			for(int i=0; i<INFO->biHeight; ++i)
			{
				black = black && ~(bmp[(INFO->biWidth + 31) / 32 * 4 * i + j / 8] & 1 << j % 8);
			}
			if(black)
			{
				OFFSET[n] = k;
				LENGTH[n] = n ? k - OFFSET[n - 1] - 1 : k - 1;
			printf("LENGTH[%i]=%hhu OFFSET[%i]=%hu\n", n, LENGTH[n], n, OFFSET[n]);
				++ n;
			}
		}
	}
	*/
	INFO->biWidth;
	INFO->biHeight;
	(INFO->biWidth + 31) / 32 * 4;
	assert(INFO->biWidth == 1280);
	assert(INFO->biHeight == 11);
	assert(INFO->biWidth % 128L == NULL);
	# pragma warning(suppress: 26451)
	BYTE *LINE = new BYTE[(INFO->biWidth + 127L) / 128L * 16L];
	for(LONG j=0; j<INFO->biWidth / 128L; ++j)
	{
		__m128i xmm = _mm_set1_epi32(-1); // _mm_set1_epi32 -> _mm_setzero_si128
		for(LONG i=0; i<INFO->biHeight; ++i)
		{
			# pragma warning(suppress: 26451) // _mm_and_si128 -> _mm_xor_si128
			xmm = _mm_and_si128(xmm, _mm_loadu_si128(reinterpret_cast<__m128i *>(bmp) + INFO->biWidth / 128L * i + j));
		}
		// _mm_xor_si128 _mm_set1_epi32
		_mm_storeu_si128(reinterpret_cast<__m128i *>(LINE) + j, _mm_xor_si128(_mm_set1_epi32(-1), xmm));
	}
	//for(int i=0; i<INFO->biWidth; ++i) printf("%c", LINE[i/8]&1<<i%8?'.':' ');
	//printf("\n");
	USHORT n=0;
	//assert(INFO->biSizeImage << 3 == INFO->biWidth * INFO->biHeight);
	assert(INFO->biWidth % 128L == NULL);
	LONG j=0;
	//for(LONG j=0; j<INFO->biWidth / 128L * 16L; ++j)
	//for(BYTE k=0; k<8; ++k)
	while(n < 255)
	{
		assert(j / 8 < (INFO->biWidth + 127L) / 128L * 16L);
	//	assert(n < 256); // WARNING: this is the end
		if(!(LINE[j / 8] & 1 << j % 8) == true)
		{
		//	printf("LENGTH[%i]=%hhu OFFSET[%i]=%hu\n", n, LENGTH[n], n, OFFSET[n]);
			OFFSET[++ n] = j ++; // identical
			OFFSET[n] = OFFSET[n - 1] + LENGTH[n - 1] + 1;
			continue;
		}
		//++ OFFSET[n];
		++ LENGTH[n];
		++ j;
	}
	delete[ ] LINE;

	CreateWindowEx(WS_EX_TOPMOST&0, szClassName, NULL, WS_SYSMENU | WS_POPUP | WS_VISIBLE, x, y, w, h, NULL, NULL, NULL, NULL);

	MSG messēji;
	while(GetMessage(&messēji, NULL, 0, 0)) {
		TranslateMessage(&messēji);
		DispatchMessage(&messēji);
	}
	UnregisterClass(szClassName, NULL);
	
	for(int n=0; n<saizu; ++n) printf("`%s'\n", fairu[n]), free(fairu[n]);
	free(fairu);

	return 0;
}
