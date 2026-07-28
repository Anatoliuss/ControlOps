#pragma once
#include <string>
#include <vector>
#include <optional>

struct InputOperation {
    int  operation_order;
    int  deadline;
    bool is_alternative;   // false for index 0, true for the rest
};

// Parse parallel comma-separated lists into input operations.
// Empty strings -> empty vector. Throws std::runtime_error on count mismatch,
// std::invalid_argument on non-integer tokens.
std::vector<InputOperation>
parseInputOperations(const std::string& orders, const std::string& deadlines);

// Max over the present (engaged) optionals. Returns std::nullopt if none present.
template <typename T>
std::optional<T> aggregateMax(const std::vector<std::optional<T>>& xs) {
    std::optional<T> best;
    for (const auto& x : xs) {
        if (!x) continue;
        if (!best || *best < *x) best = x;
    }
    return best;
}

// Min over the present (engaged) optionals. Returns std::nullopt if none present.
template <typename T>
std::optional<T> aggregateMin(const std::vector<std::optional<T>>& xs) {
    std::optional<T> best;
    for (const auto& x : xs) {
        if (!x) continue;
        if (!best || *x < *best) best = x;
    }
    return best;
}

// Business rule for combining dependency-derived dates.
// When at least one alternative dependency produced a date, the operation waits for the
// latest candidate (max); with mandatory inputs only, it takes the earliest (min).
// This is the single place the min/max rule lives — both calculation phases call it.
template <typename T>
std::optional<T> aggregateDependencyDates(const std::vector<std::optional<T>>& candidates,
                                          bool alternative_contributed) {
    return alternative_contributed ? aggregateMax(candidates) : aggregateMin(candidates);
}
