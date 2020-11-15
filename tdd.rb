require('lib/ansi_term')

def assert(condition)
    unless condition
        raise "Failed"
    end
end

# values copied from make file
Src_dir = 'src'
Test_dir = 'tests'

Command = %w|
  gcc
    -g -std=c99 -O
    -Werror -Wall -Wextra -pedantic
    -Wno-error=format -Wno-error=unused-variable
    %s
    -l cmocka
    -o %s
  |.join(' ').strip

def to_source_file(name)
    # normalize separators
    source_file = name.gsub(/\\/, File::SEPARATOR)
    # drop leading ./
    source_file = source_file.sub(/^\.#{File::SEPARATOR}/, '')
    # add src/
    if source_file !~ /^#{Src_dir}/
        source_file = Src_dir + File::SEPARATOR + source_file
    end
    # add .c
    if source_file !~ /\.c$/
        source_file += '.c'
    end

    source_file
end

def test_file_from_source_file(source_file)
    assert(File.exist?(source_file))

    file_name = source_file[/#{File::SEPARATOR}[^#{File::SEPARATOR}\.]+/][1..-1]
    # replace snake case with camel case
    test_name = '_' + file_name
    while test_name =~ /_(.)/
        rep = $1.upcase
        test_name = test_name.sub(/_(.)/, rep)
    end
    test_name += 'Test'
    # add tests/
    test_file = "#{Test_dir}#{File::SEPARATOR}#{test_name}.c"

    test_file
end

def included_files(source_file)
    assert(File.exist?(source_file))

    IO.readlines(source_file).
      find_all { |line| line =~ /^#include \"/ }.
      map { |include| include[10..-5] }.
      map { |name| to_source_file(name) }.
      find_all { |file| File.exist?(file) }
end

if __FILE__ == $0

    source = ARGV[0]

    to_compile = []
    source_file = to_source_file(source)
    assert(File.exist?(source_file))
    to_compile << source_file

    includes = included_files(source_file)
    to_compile += includes

    test_file = test_file_from_source_file(source_file)
    assert(File.exist?(test_file))
    to_compile << test_file

    test_exe = test_file_from_source_file(source_file)[0..-3] + '.exe'

    if File.exist?(test_exe)
        puts "del #{test_exe}"
        File.delete(test_exe)
    end

    c = sprintf(Command, to_compile.join(' '), test_exe)

    puts c
    puts `#{c}`
    if $?.exitstatus != 0
        puts "FAILED #{$?.exitstatus}"
        exit($?.exitstatus)
    end

    puts "#{test_exe}"
    puts `#{test_exe}`
    if $?.exitstatus != 0
        puts "FAILED #{$?.exitstatus}"
        exit($?.exitstatus)
    end
end
