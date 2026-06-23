# 11402 CI002 — C++ 程式設計實習（二）

**學生：** Hans Chen 陳柏翰
**學號：** `1110927`  
**學期：** 114 學年度第 2 學期

本倉庫收錄 C++ 程式設計實習（二）課程的所有作業、練習題與考試檔案，以 LeetCode 與 UVa Online Judge 為主要解題平台。

## 目錄結構

```text
11402_CI002/
├── Before-Class_Exercises/         # 課前練習（LeetCode）
│   └── Week##_#_LeetCode###/
│       ├── README.md
│       └── src/
│           └── LeetCode###.cpp
├── On-Site_Examinations/           # 課堂現場考試（UVa Online Judge）
│   └── Week##_#_UVa#####/
│       ├── README.md
│       └── src/
│           └── UVa#####.cpp
├── After-Class_Practices/          # 課後作業（LeetCode）
│   └── Week##_#_LeetCode###/
│       ├── README.md
│       └── src/
│           └── LeetCode###.cpp
├── Midterm/                        # 期中考（UVa Online Judge）
│   └── Regular_#_UVa#####/        # 或 Bonus_#_UVa#####/
│       ├── README.md
│       └── src/
│           └── UVa#####.cpp
├── final/                          # 期末考（UVa Online Judge）
│   └── Regular_#_UVa#####/        # 或 Bonus_#_UVa#####/
│       ├── README.md
│       └── src/
│           └── UVa#####.cpp
└── README.md                       # 本檔案
```

## 各分類說明

### 課前練習（Before-Class_Exercises）

- **平台：** [LeetCode](https://leetcode.com/)
- **說明：** 每週上課前需完成的 LeetCode 題目，用於預習當週資料結構或演算法主題。
- **資料夾數：** 23 題（Week03 ～ Week15）

### 課堂現場考試（On-Site_Examinations）

- **平台：** [UVa Online Judge](https://onlinejudge.org/)
- **說明：** 每週課堂中進行的限時考試，使用 UVa 題庫。考試時間有限，部分題目可能未完成（以 `-NF.cpp` 標示）。
- **資料夾數：** 59 題（Week01 ～ Week18）

### 課後作業（After-Class_Practices）

- **平台：** [LeetCode](https://leetcode.com/)
- **說明：** 每週課後需繳交的 LeetCode 題目，用於複習當週上課內容。
- **資料夾數：** 26 題（Week01 ～ Week14）

### 期中考（Midterm）

- **平台：** [UVa Online Judge](https://onlinejudge.org/)
- **說明：** 期中考試題目，分為必答題（Regular）與加分題（Bonus）。
- **規則檔：** `CI002_midterm_rule.pdf`

### 期末考（final）

- **平台：** [UVa Online Judge](https://onlinejudge.org/)
- **說明：** 期末考試題目，同樣分為必答題（Regular）與加分題（Bonus）。

## 命名規則

| 類別 | 資料夾格式 | 範例 |
|------|-----------|------|
| 課前練習 / 課後作業 | `Week##_#_LeetCode###` | `Week09_1_LeetCode303` |
| 課堂考試 | `Week##_#_UVa#####` | `Week14_1_UVa10252` |
| 期中 / 期末必答題 | `Regular_#_UVa#####` | `Regular_1_UVa10931` |
| 期中 / 期末加分題 | `Bonus_#_UVa#####` | `Bonus_2_UVa10810` |

- `Week##`：兩位數週次，例如 `Week09`
- `_#`：同週次內的第幾題，從 `1` 開始
- `###` / `#####`：平台題號

## 原始碼命名規則

- **已完成（Accepted）：** `UVa10252.cpp` / `LeetCode303.cpp`
- **未完成（Not Finished）：** `UVa10252-NF.cpp` / `LeetCode303-NF.cpp`

`-NF` 後綴代表該題在當次考試或作業中未能完成，程式碼可能不完整或無法通過所有測資。

## 每題資料夾的 README 結構

每個題目資料夾內的 `README.md` 包含以下區塊：

1. **題目資訊** — 平台、題號、題名、連結、原始碼路徑
2. **題意說明** — 以自己的話描述輸入、輸出、限制與核心任務
3. **解題思路** — 初始想法與最終策略
4. **虛擬碼（Pseudocode）** — 演算法步驟概述
5. **錯誤碼 vs. 正確碼** — 比較錯誤嘗試與最終解法
6. **心得與反思** — 最大失誤、習得知識、未來規劃

## 使用平台

| 平台 | 用途 | 網址 |
|------|------|------|
| LeetCode | 課前練習、課後作業 | https://leetcode.com/ |
| UVa Online Judge | 課堂考試、期中、期末 | https://onlinejudge.org/ |

## AI 協作聲明

本倉庫部分工作流程使用 AI（Claude Code）輔助，範圍如下：

| 類別 | 說明 |
|------|------|
| 題目卡關詢問 | 解題遇到困難時詢問 AI，釐清思路或排查錯誤 |
| 文件撰寫 | 各題 README.md 主體由 AI 依據當次解題 session 的程式碼與問題 prompt 作為上下文，套用既定模板生成 |
| git 操作 | 部分提交訊息與常規 git 指令由 AI 執行 |
| 專案架構整理 | 大量重構或資料夾搬移時由 AI 統一整理 |

所有解題程式碼（`src/*.cpp`）均由本人獨立撰寫；AI 未直接生成或修改解題邏輯。

## 附記

- 本倉庫為個人課程作業紀錄，僅供學習參考。
- 題目版權歸各原始出題平台（LeetCode / UVa）所有。
- 全部題目清單與平台對照表請見 `.Problems.md`。
- 倉庫結構與命名規範請見 `.project_hierarchy.md`。
- 根目錄 `README.md` 僅記錄倉庫結構與總覽資訊；各題的解題說明與心得請見各題目資料夾內的 `README.md`。
- 若某題目資料夾尚無解題筆記，代表該資料夾與 `src/` 已建立但 README 尚未填寫。
