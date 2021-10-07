#include "pch.h"
#include "framework.h"
#include "Console.h"

#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(NULL);

    if (hModule != NULL)
    {
        // MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
        if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
            _tprintf(L"심각한 오류: MFC 초기화 실패\n");
            nRetCode = 1;
        }
        else
        {
            _tsetlocale(LC_ALL, _T("korean"));

            _tprintf(_T("Assignment 2 | Console | 2020136018 김성녕\n\n"));

            // Assignment_2_1
            _tprintf(_T("Assignment 2_1 | Console\n\n"));

            CTime currentTime = CTime::GetCurrentTime();
            CString currentTimeStr = currentTime.Format("%Y-%m-%d %H:%M:%S");

            _tprintf(_T("Current time is:\t%s\n\n"), currentTimeStr);

            _tprintf(_T("========================\n\n"));

            // Assignment_2_2
            _tprintf(_T("Assignment 2_2 | Console\n\n"));

            currentTime = CTime::GetCurrentTime();
            currentTimeStr = currentTime.Format("%Y-%m-%d %H:%M:%S");

            CTime anniversary = currentTime + CTimeSpan(1000, 0, 0, 0);
            CString anniversaryStr = anniversary.Format("%Y-%m-%d %H:%M:%S");

            CTimeSpan timeDiff = anniversary - currentTime;

            _tprintf(_T("Current time is:\t%s\n"), currentTimeStr);
            _tprintf(_T("Your anniversary is:\t%s\n\n"), anniversaryStr);
            _tprintf(_T("Time Diff: %lld days\n\n"), timeDiff.GetDays());

            _tprintf(_T("========================\n\n"));

            // Assignment_2_3
            _tprintf(_T("Assignment 2_3 | Console\n\n"));

            CUIntArray array;
            int sum = 0;
            double avg = 0;

            for (int i = 1; i <= 100; i++) {
                array.Add(i);
                sum += i;
            }

            avg = sum / 100.0;

            _tprintf(_T("sum: %d\n"), sum);
            _tprintf(_T("avg: %g\n\n"), avg);

            _tprintf(_T("========================\n\n"));

            // Assignment_2_4
            _tprintf(_T("Assignment 2_4 | Console\n\n"));

            CList<int> list;

            for (int i = 0; i < 100; i++)
                list.AddTail(i + 1);

            POSITION pos = list.GetHeadPosition();
            while (pos != NULL)
                _tprintf(_T("%d "), list.GetNext(pos));
            _tprintf(_T("\n\n"));

            int input;
            _tscanf_s(_T("%d"), &input);

            POSITION prev;
            pos = list.GetHeadPosition();
            do
                prev = pos;
            while (list.GetNext(pos) != input);

            list.RemoveAt(prev);

            pos = list.GetHeadPosition();
            _tprintf(_T("\n"));
            while (pos != NULL)
                _tprintf(_T("%d "), list.GetNext(pos));
            _tprintf(_T("\n\n"));

            _tprintf(_T("========================\n"));
        }
    }
    else
    {
        // TODO: 오류 코드를 필요에 따라 수정합니다.
        _tprintf(L"심각한 오류: GetModuleHandle 실패\n");
        nRetCode = 1;
    }

    return nRetCode;
}
