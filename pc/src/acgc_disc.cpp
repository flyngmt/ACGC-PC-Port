#include "acgc/disc.hpp"

#include <borealis/log.hpp>

#include <array>

namespace acgc::disc {
namespace {

constexpr borealis::Log Log{"acgc::disc"};

constexpr auto AcceptedDiscs = std::to_array<borealis::disc::AcceptedDisc>({
    {
        .gameId = "GAFE01",
        .discNumber = 0,
        .revision = 0,
        .expectedHash = borealis::disc::parse_xxh3_128("9ffba17f08aa24e8a084ba30e038cef3"),
    },
});

constexpr auto RecognizedGameIds = std::to_array<std::string_view>({
    "GAFJ01",
    "GAFP01",
});

constexpr borealis::disc::Catalog DiscCatalog{
    .acceptedDiscs = AcceptedDiscs,
    .recognizedGameIds = RecognizedGameIds,
};

ValidationError validation_error(borealis::disc::Status status) noexcept
{
    switch (status) {
    case borealis::disc::Status::Success: return ValidationError::Success;
    case borealis::disc::Status::IOError: return ValidationError::IOError;
    case borealis::disc::Status::InvalidImage: return ValidationError::InvalidImage;
    case borealis::disc::Status::UnknownGame: return ValidationError::WrongGame;
    case borealis::disc::Status::UnsupportedVersion: return ValidationError::WrongVersion;
    case borealis::disc::Status::Canceled: return ValidationError::Canceled;
    case borealis::disc::Status::HashMismatch: return ValidationError::HashMismatch;
    case borealis::disc::Status::Failed:
    default: return ValidationError::Unknown;
    }
}

void update_info(const borealis::disc::Result& result, DiscInfo& info)
{
    info = {
        .gameId = result.metadata.gameId,
        .title = result.metadata.title,
        .discNumber = result.metadata.discNumber,
        .revision = result.metadata.revision,
    };
}

} // namespace

ValidationError inspect(std::string_view path, DiscInfo& info)
{
    const auto result = borealis::disc::inspect(path, DiscCatalog);
    update_info(result, info);
    return validation_error(result.status);
}

ValidationError verify(std::string_view path, VerificationStatus& status, DiscInfo& info)
{
    const auto result = borealis::disc::verify(path, DiscCatalog, &status);
    update_info(result, info);
    return validation_error(result.status);
}

void log_verification_state(std::string_view path, DiscVerificationState state)
{
    const char* label = state == DiscVerificationState::Success ? "verified"
        : state == DiscVerificationState::HashMismatch ? "hash mismatch"
                                                        : "unknown";
    Log.info("Disc verification status: {} (path: {})", label, path.empty() ? "<none>" : path);
}

} // namespace acgc::disc
