#include "settings/SourceGroupSettingsJavaMaven.h"

SourceGroupSettingsJavaMaven::SourceGroupSettingsJavaMaven(const std::string& id, const ProjectSettings* projectSettings)
	: SourceGroupSettingsJava(id, SOURCE_GROUP_JAVA_MAVEN, projectSettings)
	, m_mavenProjectFilePath(FilePath())
	, m_mavenDependenciesDirectory(FilePath())
	, m_shouldIndexMavenTests(false)
{
}

SourceGroupSettingsJavaMaven::~SourceGroupSettingsJavaMaven()
{
}

void SourceGroupSettingsJavaMaven::load(std::shared_ptr<const ConfigManager> config)
{
	SourceGroupSettingsJava::load(config);

	const std::string key = s_keyPrefix + getId();

	setMavenProjectFilePath(FilePath(getValue<std::string>(key + "/maven/project_file_path", "", config)));
	setMavenDependenciesDirectory(FilePath(getValue<std::string>(key + "/maven/dependencies_directory", "", config)));
	setShouldIndexMavenTests(getValue<bool>(key + "/maven/should_index_tests", false, config));
}

void SourceGroupSettingsJavaMaven::save(std::shared_ptr<ConfigManager> config)
{
	SourceGroupSettingsJava::save(config);

	const std::string key = s_keyPrefix + getId();

	setValue(key + "/maven/project_file_path", getMavenProjectFilePath().str(), config);
	setValue(key + "/maven/dependencies_directory", getMavenDependenciesDirectory().str(), config);
	setValue(key + "/maven/should_index_tests", getShouldIndexMavenTests(), config);
}

bool SourceGroupSettingsJavaMaven::equals(std::shared_ptr<SourceGroupSettings> other) const
{
	std::shared_ptr<SourceGroupSettingsJavaMaven> otherJavaMaven = std::dynamic_pointer_cast<SourceGroupSettingsJavaMaven>(other);

	return (
		otherJavaMaven &&
		SourceGroupSettingsJava::equals(other) &&
		m_mavenProjectFilePath == otherJavaMaven->m_mavenProjectFilePath &&
		m_mavenDependenciesDirectory == otherJavaMaven->m_mavenDependenciesDirectory &&
		m_shouldIndexMavenTests == otherJavaMaven->m_shouldIndexMavenTests
	);
}

FilePath SourceGroupSettingsJavaMaven::getMavenProjectFilePath() const
{
	return m_mavenProjectFilePath;
}

FilePath SourceGroupSettingsJavaMaven::getMavenProjectFilePathExpandedAndAbsolute() const
{
	return m_projectSettings->makePathExpandedAndAbsolute(getMavenProjectFilePath());
}

void SourceGroupSettingsJavaMaven::setMavenProjectFilePath(const FilePath& path)
{
	m_mavenProjectFilePath = path;
}

FilePath SourceGroupSettingsJavaMaven::getMavenDependenciesDirectory() const
{
	return m_mavenDependenciesDirectory;
}

FilePath SourceGroupSettingsJavaMaven::getMavenDependenciesDirectoryExpandedAndAbsolute() const
{
	return m_projectSettings->makePathExpandedAndAbsolute(getMavenDependenciesDirectory());
}

void SourceGroupSettingsJavaMaven::setMavenDependenciesDirectory(const FilePath& path)
{
	m_mavenDependenciesDirectory = path;
}

bool SourceGroupSettingsJavaMaven::getShouldIndexMavenTests() const
{
	return m_shouldIndexMavenTests;
}

void SourceGroupSettingsJavaMaven::setShouldIndexMavenTests(bool value)
{
	m_shouldIndexMavenTests = value;
}