#include "./compute.h"

// extract functions
ubyte e_num(ubyte card)
{
    return card & 0x0f;
}
ubyte e_color(ubyte card)
{
    return card >> 4;
}

SCOREFN(evaluate_card_management, {
    ubyte colors_counts[MAX_COLORS + 1] = {0};
    DBLIST node = hand;
    while (node)
    {
        colors_counts[e_color(node->val)]++;
        node = node->next;
    }

    scoreadd colors_counts[e_color(card)] * (e_color(card) == e_color(leading));
})

SCOREFN(evaluate_card_matching, {
    ubyte colors_counts[MAX_COLORS + 1] = {0};
    DBLIST node = hand;
    while (node)
    {
        colors_counts[e_color(node->val)]++;
        node = node->next;
    }
    scoreadd 3 * (e_color(card) == e_color(leading) || e_color(card) == UNO_BLACK);
    scoreadd 3 * (colors_counts[e_color(card)] == 1 && e_num(card) < 10 && e_num(leading) < 10);
    scoreadd 10 * -(e_num(card) > 12 && colors_counts[e_color(leading)] > 0);
})

byte evaluate_move(ubyte card, DBLIST hand, ubyte leading)
{

    SCOREFN_VARIABLE(scorefns[]) = {evaluate_card_matching, evaluate_card_management};
    return scorefns[e_num(card) > 9 && e_num(card) < 13](card, hand, leading);
}

ubyte heauristic_alg(DBLIST array, ubyte leading)
{
    ubyte best_card = -1;
    byte score, best_score = 1 << 7;

    DBLIST node = array;
    while (node)
    {
        score = evaluate_move(node->val, array, leading);
        (score > best_score) && (best_score = score,
                                 best_card = node->val);

        node = node->next;
    }

    return best_card;
}
ubyte prioritise_color(DBLIST hand)
{
    ubyte colors_counts[MAX_COLORS + 1] = {0};
    DBLIST node = hand;

    ubyte best_color = UNO_BLACK, best_color_counts = 0, current;
    bool condition;
    while (node)
    {
        current = e_color(node->val);
        colors_counts[current]++;
        node = node->next;

        condition = best_color_counts < colors_counts[current] && current < UNO_BLACK;

        best_color_counts = !condition * best_color_counts + condition * colors_counts[current];
        best_color = !condition * best_color + condition * current;
    }

    return best_color;
}