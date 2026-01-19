#include "stock_market.h"

Person* create_person(char *name, int id) {
    /* WRITE YOUR CODE HERE AND REMOVE RETURN NULL */
    Person* person = (Person*)malloc(sizeof(Person));
    int i;
    for (i=0; name[i] != '\0'; i++) person->name[i] = name[i];
    person->name[i] = '\0';
    person->id = id;
    return person;
}

Company* create_company(char *name, char *abbr, int order) {
    /* WRITE YOUR CODE HERE AND REMOVE RETURN NULL */
    Company* company = (Company*)malloc(sizeof(Company));
    int i;
    for (i=0; name[i] != '\0'; i++) company->name[i] = name[i];
    company->name[i] = '\0';
    for (i=0; abbr[i] != '\0'; i++) company->stock_abbreviation[i] = abbr[i];
    company->stock_abbreviation[i] = '\0';
    company->market_order = order;
    return company;
}

void add_company_to_market(StockMarket *market, Company *company) {
    /* WRITE YOUR CODE HERE */
    market->entries[company->market_order - 1].company = company;
    market->entries[company->market_order - 1].buy_requests = NULL;
    market->entries[company->market_order - 1].sell_requests = NULL;
    market->company_count++;
}

RequestNode* create_request_node(Person *p, int amount, float price) {
    /* WRITE YOUR CODE HERE AND REMOVE RETURN NULL */
    RequestNode* node = (RequestNode*)malloc(sizeof(RequestNode));
    node->data.person = p;
    node->data.amount = amount;
    node->data.price_per_share = price;
    node->next = NULL;
    return node;
}

void insert_sorted(RequestNode **head, RequestNode *node, int ascending) {
    /* WRITE YOUR CODE HERE */
    if (ascending == 1) { /*Buy requests*/
        RequestNode* current, *prev;
        if ((*head) == NULL) {
            (*head) = node;
            return;
        }
        if ((*head)->data.price_per_share < node->data.price_per_share) {
            node->next = (*head);
            (*head) = node;
            return;
        }
        current = (*head); prev = NULL;
        while (current && node->data.price_per_share <= current->data.price_per_share) {
            prev = current;
            current = current->next;
        }
        prev->next = node;
        node->next = current;
        return;
    } else if (ascending == -1) {
        RequestNode* current, *prev;
        if ((*head) == NULL) {
            (*head) = node;
            return;
        }
        if ((*head)->data.price_per_share > node->data.price_per_share) {
            node->next = (*head);
            (*head) = node;
            return;
        }
        current = (*head); prev = NULL;
        while (current && node->data.price_per_share >= current->data.price_per_share) {
            prev = current;
            current = current->next;
        }
        prev->next = node;
        node->next = current;
        return;
    }
}

void insert_buy_request(StockMarket *market, Person **people, int people_count, char *buyer_name, char *company_abbr, int amount, float price) {
    /* WRITE YOUR CODE HERE */
    Person* person = create_person(buyer_name, -1);
    RequestNode* node, **sell;
    int i;
    for (i=0; i<people_count; i++) {
        if (strcmp(people[i]->name, buyer_name) == 0) {
            person->id = people[i]->id;
        }
    }
    node = create_request_node(person, amount, price);
    for (i=0; i<market->company_count; i++) {
        if (strcmp(company_abbr, market->entries[i].company->stock_abbreviation) == 0) {
            sell =  &(market->entries[i].sell_requests);
            break;
        }
    }
    while ((*sell) != NULL && node->data.price_per_share >= (*sell)->data.price_per_share) {
        RequestNode* temp = (*sell);
        if (node->data.amount > (*sell)->data.amount) {
            node->data.amount -= (*sell)->data.amount;
            printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", (*sell)->data.amount, market->entries[i].company->stock_abbreviation, (*sell)->data.price_per_share, (*sell)->data.person->name, person->name);
            (*sell) = (*sell)->next;
            free(temp);
        } else if (node->data.amount < (*sell)->data.amount) {
            (*sell)->data.amount -= node->data.amount;
            printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", node->data.amount, market->entries[i].company->stock_abbreviation, (*sell)->data.price_per_share, (*sell)->data.person->name, person->name);
            free(node);
            node = NULL;
            break;
        } else {
            printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", node->data.amount, market->entries[i].company->stock_abbreviation, (*sell)->data.price_per_share, (*sell)->data.person->name, person->name);
            (*sell) = (*sell)->next;
            free(temp);
            free(node);
            node = NULL;
            break;
        }
    }
    if (node != NULL) {
        RequestNode** buy;
        buy = &(market->entries[i].buy_requests);
        insert_sorted(buy, node, 1);
    }
}

void insert_sell_request(StockMarket *market, Person **people, int people_count, char *seller_name, char *company_abbr, int amount, float price) {
    /* WRITE YOUR CODE HERE */
    Person* person = create_person(seller_name, -1);
    int i;
    RequestNode* node, **buy;
    for (i=0; i<people_count; i++) {
        if (strcmp(people[i]->name, seller_name) == 0) {
            person->id = people[i]->id;
        }
    }
    node = create_request_node(person, amount, price);
    for (i=0; i<market->company_count; i++) {
        if (strcmp(market->entries[i].company->stock_abbreviation, company_abbr) == 0) {
            buy = &(market->entries[i].buy_requests);
            break;
        }
    }
    while ((*buy) != NULL && node->data.price_per_share <= (*buy)->data.price_per_share) {
        RequestNode* temp = (*buy);
        if (node->data.amount > (*buy)->data.amount) {
            node->data.amount -= (*buy)->data.amount;
            printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", (*buy)->data.amount, market->entries[i].company->stock_abbreviation, node->data.price_per_share, person->name, (*buy)->data.person->name);
            (*buy) = (*buy)->next;
            free(temp);
        } else if (node->data.amount < (*buy)->data.amount) {
            (*buy)->data.amount -= node->data.amount;
            printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", node->data.amount, market->entries[i].company->stock_abbreviation, node->data.price_per_share, person->name, (*buy)->data.person->name);
            free(node);
            node = NULL;
            break;
        } else {
            printf("Trade executed: %d shares of %s at %.2f between %s, %s\n", (*buy)->data.amount, market->entries[i].company->stock_abbreviation, node->data.price_per_share, person->name, (*buy)->data.person->name);
            (*buy) = (*buy)->next;
            free(temp);
            free(node);
            node = NULL;
            break;
        }
    }
    if (node != NULL) {
        RequestNode** sell;
        sell = &(market->entries[i].sell_requests);
        insert_sorted(sell, node, -1);
    }
}

void print_market(StockMarket *market) {
    /* WRITE YOUR CODE HERE */
    int i;
    for (i=0; i<market->company_count; i++) {
        RequestNode* buy, *sell;
        buy = (market->entries[i].buy_requests);
        sell = (market->entries[i].sell_requests);
        printf("Company: %s (%s)\n", market->entries[i].company->name, market->entries[i].company->stock_abbreviation);
        printf("\tBuy Requests:\n");
        while (buy != NULL) {
            printf("\t\t%s wants %d @ %.2f\n", buy->data.person->name, buy->data.amount, buy->data.price_per_share);
            buy = buy->next;
        }
        printf("\tSell Requests:\n");
        while (sell != NULL) {
            printf("\t\t%s sells %d @ %.2f\n", sell->data.person->name, sell->data.amount, sell->data.price_per_share);
            sell = sell->next;
        }
    }
}
