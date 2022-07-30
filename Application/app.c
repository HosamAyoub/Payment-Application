/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: App					*********************************/
/********************************************************************************************/
/********************************************************************************************/
#include "app.h"

void main(void)
{
    appStart();
}

void appStart(void)
{
    uint8_t transactionState;
    ST_cardData_t cardInfo;
    ST_terminalData_t terminalInfo;

    // Card Layer
    if (getCardHolderName(&cardInfo) == WRONG_NAME)
    {
        printf("Declined.\nWrong Name!\n");
        return;
    }
    if (getCardExpiryDate(&cardInfo) == WRONG_EXP_DATE)
    {
        printf("Declined.\nWrong expiry date!\n");
        return;
    }
    if (getCardPAN(&cardInfo) == WRONG_PAN)
    {
        printf("Declined.\nWrong Primary Account Number!\n");
        return;
    }

    // Terminal Layer
    if (isValidCardPAN(&cardInfo) == INVALID_CARD)
    {
        printf("Declined.\nInvalid card ID!\n");
        return;
    }
    if (getTransactionDate(&terminalInfo) == WRONG_DATE)
    {
        printf("Declined.\nWrong Date!\n");
        return;
    }
    if (isCardExpired(cardInfo, terminalInfo) == EXPIRED_CARD)
    {
        printf("Declined.\nExpired card!\n");
        return;
    }
    if (getTransactionAmount(&terminalInfo) == INVALID_AMOUNT)
    {
        printf("Declined.\nInvalid amount!\n");
        return;
    }
    if (isBelowMaxAmount(&terminalInfo) == EXCEED_MAX_AMOUNT)
    {
        printf("Declined.\nYou can't Exceed %d that is the Maximum amount.\n", MAXIMUM_TRANSACTION_AMOUNT);
        return;
    }

    // Server Layer
    ST_transaction_t transactionInfo = {cardInfo, terminalInfo};
    transactionState = recieveTransactionData(&transactionInfo);
    if (transactionState == APPROVED)
    {
        printf("Approved.\n");
    }
    else if (transactionState == DECLINED_STOLEN_CARD)
    {
        printf("Declined.\nIt's a stolen!\n");
    }
    else if (transactionState == DECLINED_INSUFFECIENT_FUND)
    {
        printf("Declined.\nInsuffecient fund!\n");
    }
    else if (transactionState == INTERNAL_SERVER_ERROR)
    {
        printf("Declined.\nInternal Server Error!\n");
    }
}