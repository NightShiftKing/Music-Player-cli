class MusicPlayerCli < Formula
  desc "Terminal UI music player built with FTXUI and miniaudio"
  homepage "https://github.com/NightShiftKing/Music-Player-cli"
  url "https://github.com/NightShiftKing/Music-Player-cli/archive/refs/tags/v1.0.0.tar.gz"
  # sha256 "UPDATE_THIS_AFTER_FIRST_RELEASE"
  license "MIT"

  depends_on "cmake" => :build

  def install
    system "cmake", "-B", "build", *std_cmake_args
    system "cmake", "--build", "build"
    system "cmake", "--install", "build", "--prefix", prefix
  end

  test do
    assert_predicate bin/"music-player", :exist?
  end
end
