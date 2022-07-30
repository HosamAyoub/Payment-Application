/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: Terminal				*********************************/
/********************************************************************************************/
/********************************************************************************************/
#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../Library/STD_Types.h"
#include "../Card/card.h"

typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#define EXPIRATION_DECADE                               3
#define EXPIRATION_YEAR                                 4
#define EXPIRATION_TENS_MONTHS                          0
#define EXPIRATION_MONTH                                1

#define TRANSACTION_DECADE                              8
#define TRANSACTION_YEAR                                9
#define TRANSACTION_TENS_MONTHS                         3
#define TRANSACTION_MONTH                               4

#define MAXIMUM_TRANSACTION_AMOUNT                      50000

#endif