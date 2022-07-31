/********************************************************************************************/
/********************************************************************************************/
/********************			Author: Hosam Ayoub			*********************************/
/********************			Layer: App					*********************************/
/********************************************************************************************/
/********************************************************************************************/
#include "app.h"

void main(void)
{
    uint8_t Exit = 0;
    while (Exit != 'Q' && Exit != 'q')
    {
        appStart();
        printf("\nEnter Q to shutdown the system or any key to continue: ");
        scanf(" %c", &Exit);
    }
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

    ST_transaction_t transactionInfo = {cardInfo, terminalInfo};
    uint8_t option = 0;
    uint32_t transactionSequenceNumber;
    while (option != 3)
    {
        printf("\nTo to do a Transaction Enter 1\n");
        printf("To search for Transaction Enter 2\n");
        printf("To exit Enter 3\n");
        printf("Your Choice: ");
        scanf(" %d", &option);
        if (getTransactionDate(&terminalInfo) == WRONG_DATE)
        {
            printf("Declined.\nWrong Date!\n");
            return;
        }
        printf("Transaction Date: %s\n", terminalInfo.transactionDate);
        if (option == 1)
        {
            // Terminal Layer
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
            transactionInfo.cardHolderData = cardInfo;
            transactionInfo.terminalData = terminalInfo;

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
        else if (option == 2)
        {
            printf("To search for a transaction Enter it sequence number: ");
            scanf("%d", &transactionSequenceNumber);
            getTransaction(transactionSequenceNumber, &transactionInfo);
        }
        else
        {
            printf("Invalid input!\n");
        }
    }
}