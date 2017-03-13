--
-- File generated with SQLiteStudio v3.0.3 on So Mrz 22 09:30:31 2015
--
-- Text encoding used: windows-1252
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: content_types_fields_types
CREATE TABLE "content_types_fields_types" (
	`field_type_id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`type`	VARCHAR(48)
);
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (1, 'button');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (2, 'checkbox');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (3, 'color');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (4, 'date');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (5, 'datetime');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (6, 'datetime-local');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (7, 'email');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (8, 'fieldset');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (9, 'file');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (10, 'hidden');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (11, 'html');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (12, 'image');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (13, 'month');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (14, 'number');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (15, 'password');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (16, 'radio');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (17, 'range');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (18, 'reset');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (19, 'search');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (20, 'select');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (21, 'submit');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (22, 'tel');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (23, 'text');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (24, 'textarea');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (25, 'time');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (26, 'url');
INSERT INTO content_types_fields_types (field_type_id, type) VALUES (27, 'week');

COMMIT TRANSACTION;
