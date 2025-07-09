#ifndef HISTORYVIEWER_HPP
#define HISTORYVIEWER_HPP

#include <vector>
#include <string>

class HistoryViewer {
public:
    HistoryViewer();
    ~HistoryViewer();

    void loadHistory(const std::string& deviceId, int days);
    void displayHistory() const;

private:
    struct HistoryData {
        std::string timestamp;
        std::string data;
    };

    std::vector<HistoryData> historyRecords;
};

#endif // HISTORYVIEWER_HPP