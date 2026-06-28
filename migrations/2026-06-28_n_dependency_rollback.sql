-- Rollback migration: restore the two-slot schema.
-- NOTE: lossy for input_* — only the FIRST dependency survives the integer cast.
-- For a full restore, reload the old Excel or restore from
-- static_initial_data_control_operations_backup_20260628.
BEGIN;

ALTER TABLE static_initial_data_control_operations
    ADD COLUMN IF NOT EXISTS alternative_operation_order integer,
    ADD COLUMN IF NOT EXISTS alternative_deadline        integer;

ALTER TABLE static_initial_data_control_operations
    ALTER COLUMN input_operation_order TYPE integer
        USING NULLIF(split_part(input_operation_order, ',', 1), '')::integer,
    ALTER COLUMN input_deadline TYPE integer
        USING NULLIF(split_part(input_deadline, ',', 1), '')::integer;

COMMIT;
