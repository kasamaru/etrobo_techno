/**
 * @brief コンパイルスイッチ
 */

/* コース選択定義 */
/* 右コース用定義 */
#define COURCE_RIGHT

#ifndef COURCE_RIGHT
/* 左コース用定義 */
#define COURCE_LEFT
#endif

/* ログ出力用定義 */
#ifdef LOF_ACTIVE
#define LOG_ACTIVE
#else

#endif
