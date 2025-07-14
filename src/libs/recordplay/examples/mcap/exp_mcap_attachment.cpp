#define MCAP_IMPLEMENTATION
#include <mcap/reader.hpp>
#include <mcap/writer.hpp>

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

int main()
{
    const std::string tstString1 = "Hello mcap Attachment-1!";
    const std::string tstString2 = "Hello mcap Attachment-2!";
    const std::string mcapFilePath = EXECUTABLE_OUTPUT_PATH + std::string("/mcap-attachment.mcap");

    mcap::McapWriter writer;
    mcap::McapWriterOptions options("ros2");
    auto status = writer.open(mcapFilePath, options);
    if (!status.ok())
    {
        std::cerr << "Failed to open file: " << status.message << "\n";
        return -1;
    }
    // 创建附件元数据
    mcap::Attachment attachment1;
    attachment1.name = "tst-string1";
    attachment1.mediaType = "string";
    attachment1.createTime = std::chrono::system_clock::now().time_since_epoch().count();
    attachment1.data = reinterpret_cast<const std::byte*>(tstString1.data());
    attachment1.dataSize = tstString1.size();
    writer.write(attachment1);
    mcap::Attachment attachment2;
    attachment2.name = "tst-string2";
    attachment2.mediaType = "string";
    attachment2.createTime = std::chrono::system_clock::now().time_since_epoch().count();
    attachment2.data = reinterpret_cast<const std::byte*>(tstString2.data());
    attachment2.dataSize = tstString2.size();
    writer.write(attachment2);
    // 写入附件
    writer.close();

    mcap::McapReader reader;
    status = reader.open(mcapFilePath);
    if (!status.ok())
    {
        std::cerr << "Failed to open file: " << status.message << "\n";
        return -1;
    }
    // 遍历所有附件
    reader.readSummary(mcap::ReadSummaryMethod::NoFallbackScan);
    const auto &indexes = reader.attachmentIndexes();
    for (const auto& index : indexes)
    {
        mcap::Record record;
        mcap::Attachment attachment;
        const mcap::AttachmentIndex &attachmentIndex = index.second;
        mcap::McapReader::ReadRecord(*reader.dataSource(), attachmentIndex.offset, &record);
        mcap::McapReader::ParseAttachment(record, &attachment);
        std::cout << "read Attachment:name=" << index.first
                  << ", data=" << std::string(reinterpret_cast<const char*>(attachment.data),
                                              reinterpret_cast<const char*>(attachment.data) + attachment.dataSize)
                  << std::endl;
    }
    reader.close();

    return 0;
}
