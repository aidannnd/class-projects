<?php


class SiteTest extends \PHPUnit\Framework\TestCase {
    public function test_defaults() {
        $site = new Felis\Site();

        $site->setEmail("test@test.com");
        $site->setRoot("test");
        $site->dbConfigure("host", "user", "password", "prefix");

        $this->assertEquals($site->getEmail(), "test@test.com");
        $this->assertEquals($site->getRoot(), "test");
        $this->assertEquals($site->getTablePrefix(), "prefix");
    }

    public function test_localize() {
        $site = new Felis\Site();
        $localize = require 'localize.inc.php';
        if(is_callable($localize)) {
            $localize($site);
        }
        $this->assertEquals('test_', $site->getTablePrefix());
    }
}